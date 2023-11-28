#include "ItemActor.h"
#include "AdventureCharacter.h"
#include "AdventureGameModeBase.h"

AItemActor::AItemActor()
{
	Logger = CreateDefaultSubobject<ULogging>(TEXT("Logger"));
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AItemActor::OnOverlapEnd);


	PickUpSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PickUpSoundComponent"));
	PickUpSoundComponent->bAutoActivate = false;
	PickUpSoundComponent->SetupAttachment(RootComponent);

	UseSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("UseSoundComponent"));
	UseSoundComponent->bAutoActivate = false;
	UseSoundComponent->SetupAttachment(RootComponent);

	DropSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DropSoundComponent"));
	DropSoundComponent->bAutoActivate = false;
	DropSoundComponent->SetupAttachment(RootComponent);

}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
	}
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemActor::SetCharacter(AAdventureCharacter* ItemCharacter)
{
	Character = ItemCharacter;
}

void AItemActor::Log(FString LogMessage) 
{
	GEngine->AddOnScreenDebugMessage(LogKey, LogTime, LogColor, LogMessage);
}

void AItemActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// Log("NotifyHit: " + GetName() + " <- " + (Other ? Other->GetName() : "None"));
	if (Character && Character == Other) 
	{
		return;
	}
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (!Character && Other && Character != Other) {
		AAdventureCharacter* TargetCharacter = Cast<AAdventureCharacter>(Other);
		if (TargetCharacter && TargetCharacter->PuckUpItems)
		{
			TargetCharacter->PickupItem(this, TargetCharacter->ItemsSlot);
		}
	}
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AAdventureCharacter* TargetCharacter = Cast<AAdventureCharacter>(OtherActor);
	// Log("OnOverlapBegin: " + GetName() + " <- " + (OtherActor ? OtherActor->GetName() : "None"));
	if (!Character) {
		if (TargetCharacter && TargetCharacter->IsPlayer)
		{

			TargetCharacter->PickupItem(this, GetCharacterItemSlot(TargetCharacter, false));
		}
		else
		{
			AVehicle* TargetVehicle = Cast<AVehicle>(OtherActor);
			if (TargetVehicle && TargetVehicle->DriverCharacter) {
				TargetVehicle->DriverCharacter->PickupItem(this, GetCharacterItemSlot(TargetVehicle->DriverCharacter, false));
			}

		}
	}	

}

void AItemActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// This function is called when the actor stops overlapping with 'OtherActor'
	// You can perform actions related to the end of overlap here
}

void AItemActor::PickedUpByCharacter(AAdventureCharacter* TargetCharacter, bool AsDefault, FName SlotName)
{

	TriggerPickUpEffects(TargetCharacter);
	if (TargetCharacter) 
	{
		Character = TargetCharacter;
		Character->AddItem(this);
		TArray<USceneComponent*> AllComponents;
		GetComponents(AllComponents);
		for (USceneComponent* Component : AllComponents)
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component);
			if (PrimitiveComponent)
			{
				PrimitiveComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			}
		}
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(Character->GetMesh(), AttachmentRules, SlotName);
		Hide();
		TargetCharacter->Log("PickedUpByCharacter");
	}
	OnPickedUpByCharacter(TargetCharacter, AsDefault, SlotName);
}

void AItemActor::OnPickedUpByCharacter_Implementation(AAdventureCharacter* TargetCharacter, bool AsDefault, FName SlotName)
{
	// can be overwitten by blueprint
}


void AItemActor::TriggerPickUpEffects(AAdventureCharacter* TargetCharacter)
{
	UWorld* World = GetWorld();

	if (PickUpParticles)
	{
		if (World)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				World,
				PickUpParticles,
				(GetActorLocation() + PickUpParticlesLocation),
				GetActorRotation()
			);
		}
	}
	if (PickUpSoundComponent) {
		if (!PickUpSoundComponent->IsPlaying())
		{
			PickUpSoundComponent->Play();
		}
	}
	if (TargetCharacter)
	{
		if (PickUpCharacterParticles)
		{
			FName ParticleComponentName = ItemName.IsEmpty() ? FName(TEXT("ItemParticles")) : FName(*ItemName + FString(" ItemParticles"));
			UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				PickUpCharacterParticles,
				TargetCharacter->GetRootComponent(),
				ParticleComponentName,
				PickUpCharacterParticlesLocation,
				FRotator(0.0f, 0.0f, 0.0f),
				EAttachLocation::KeepRelativeOffset,
				true
			);
		}
	}
}

void AItemActor::TriggerUseEffects()
{
	UWorld* World = GetWorld();
	if (PickUpParticles)
	{
		if (World && !Character)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				World,
				PickUpParticles,
				(GetActorLocation() + UseParticlesLocation),
				GetActorRotation()
			);
		}
		else 
		{
			FName ParticleComponentName = ItemName.IsEmpty() ? FName(TEXT("ItemParticles")) : FName(*ItemName + FString(" ItemParticles"));
			UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				PickUpParticles,
				Character->GetRootComponent(),
				ParticleComponentName,
				UseParticlesLocation,
				FRotator(0.0f, 0.0f, 0.0f),
				EAttachLocation::KeepRelativeOffset,
				true
			);
		}
	}
	if (UseSoundComponent) {
		if (!UseSoundComponent->IsPlaying())
		{
			UseSoundComponent->Play();
		}
	}
}

void AItemActor::TriggerDropEffects(AAdventureCharacter* TargetCharacter, bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && !TargetCharacter && DropParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			DropParticles,
			(GetActorLocation() + DropParticlesLocation),
			GetActorRotation()
		);
	}
	if (TargetCharacter && DropCharacterParticles)
	{
		FName ParticleComponentName = ItemName.IsEmpty() ? FName(TEXT("ItemParticles")) : FName(*ItemName + FString(" ItemParticles"));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			DropCharacterParticles,
			TargetCharacter->GetRootComponent(),
			ParticleComponentName,
			DropCharacterParticlesLocation,
			FRotator(0.0f, 0.0f, 0.0f),
			EAttachLocation::KeepRelativeOffset,
			true
		);
	}
	if (PlaySound && DropSoundComponent) {
		if (!DropSoundComponent->IsPlaying())
		{
			DropSoundComponent->Play();
		}
	}
}


FName AItemActor::GetCharacterItemSlot(AAdventureCharacter* TargetCharacter, bool FromInventar)
{
	if (TargetCharacter->PrimaryWeapon) {
		return TargetCharacter->SecondaryWeaponSlot;
	}
	return TargetCharacter->PrimaryWeaponSlot;
}

void AItemActor::Drop()
{
	UWorld* World = GetWorld();
	TriggerDropEffects(Character, true);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Character = nullptr;
	TArray<USceneComponent*> AllComponents;
	GetComponents(AllComponents);
	for (USceneComponent* Component : AllComponents)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component);
		if (PrimitiveComponent)
		{
			PrimitiveComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		}
	}
	Show();
	TriggerDropEffects(nullptr, false);
}

void AItemActor::Use()
{

}

void AItemActor::Show()
{
	SetActorHiddenInGame(false);
}

void AItemActor::Hide()
{
	SetActorHiddenInGame(true);
}

void AItemActor::ShowSpeechBuuble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter)
{
	if (GameMode) {
		if (SpeechBubble) {
			SpeechBubble->Hide();
		}
		SpeechBubble = GameMode->AddSpeechBubble(
			FText::FromString(Text),
			FontSize,
			Duration,
			new FVector(0.0f, 0.0f, 0.0f),
			new FRotator(0.0f, 90.0f, 0.0f),
			new FVector(1.0f, 1.0f, 1.0f),
			this,
			TargetCharacter,
			&SpeechBubbleClass
		);
		if (SpeechBubble)
		{
			SpeechBubble->Item = this;
		}
	}
}