
#include "DraggableActor.h"
#include "../AdventureGameModeBase.h"
#include "../GameCharacter.h"

ADraggableActor::ADraggableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootMesh->OnComponentBeginOverlap.AddDynamic(this, &ADraggableActor::OnOverlapBegin);
	RootMesh->OnComponentEndOverlap.AddDynamic(this, &ADraggableActor::OnOverlapEnd);
	RootMesh->OnComponentHit.AddDynamic(this, &ADraggableActor::OnHit);
	RootComponent = RootMesh;

	DragSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DragSoundComponent"));
	DragSoundComponent->bAutoActivate = false;
	DragSoundComponent->SetupAttachment(RootComponent);

	DropSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DropSoundComponent"));
	DropSoundComponent->bAutoActivate = false;
	DropSoundComponent->SetupAttachment(RootComponent);

	ThrowSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ThrowSoundComponent"));
	ThrowSoundComponent->bAutoActivate = false;
	ThrowSoundComponent->SetupAttachment(RootComponent);

	HitSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSoundComponent"));
	HitSoundComponent->bAutoActivate = false;
	HitSoundComponent->SetupAttachment(RootComponent);

	DestroySoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DestroySoundComponent"));
	DestroySoundComponent->bAutoActivate = false;
	DestroySoundComponent->SetupAttachment(RootComponent);
}

void ADraggableActor::BeginPlay()
{
	Super::BeginPlay();
	InitDraggableActor();
	InitialCollisionProfile = RootMesh->GetCollisionEnabled();
}

void ADraggableActor::InitDraggableActor()
{
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
	if (Draggable && GameMode && !GameMode->DraggableActors.Contains(this))
	{
		GameMode->DraggableActors.Add(this);
	}
}

void ADraggableActor::GetsGrabbed(AGameCharacter* ByCharacter)
{
	ByCharacter->GrabbedActor = this;
	LastDragCharacter = ByCharacter;
	InitialCollisionProfile = RootMesh->GetCollisionEnabled();
	RootMesh->SetSimulatePhysics(false);
	RootMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachToComponent(ByCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CharacterDraggableActorSlot);
	SetActorLocation(GetActorLocation() + DragLocation);
	TriggerDragEffects(ByCharacter, true);
}

void ADraggableActor::GetsDropped(AGameCharacter* ByCharacter)
{
	LastDragCharacter = ByCharacter;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(ByCharacter->GetActorLocation() + (ByCharacter->ActorDropLocation * ByCharacter->GetActorForwardVector()));
	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetCollisionEnabled(InitialCollisionProfile);
	if (ByCharacter->GrabbedActor == this)
	{
		ByCharacter->GrabbedActor = nullptr;
	}
	TriggerDropEffects(ByCharacter, true);
}

void ADraggableActor::GetsThrown(AGameCharacter* ByCharacter, FVector TargetLocation)
{
	LastDragCharacter = ByCharacter;
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	FVector Force = Direction * ByCharacter->ThrowDraggableActorForce * ThrowForceFactor;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(ByCharacter->GetActorLocation() + (ByCharacter->ActorStartThrowLocation * ByCharacter->GetActorForwardVector()));
	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetCollisionEnabled(InitialCollisionProfile);
	RootMesh->AddImpulse(Force, NAME_None, true);
	if (ByCharacter->GrabbedActor == this)
	{
		ByCharacter->GrabbedActor = nullptr;
	}
	TriggerThrowEffects(ByCharacter, true);
}


void ADraggableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADraggableActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float ImpulseStrength = GetVelocity().Size();
	if ((OtherActor == this) || (LastDragCharacter == OtherActor) || ImpulseStrength < MinHitImpulseStrength)
	{
		return;
	}
	ObjectHits++;
	AGameCharacter* OtherCharacter = Cast<AGameCharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->TakeDamageAtLocation(ImpulseStrength * ThrowDamageFactor, GetActorLocation(), GetVelocity() * ThrowImpulseStength, this);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * ThrowImpulseStength, GetActorLocation());
	}
	TriggerHitEffects(OtherCharacter, true);
	if (DestroyAfterHits > 0 && ObjectHits == DestroyAfterHits) 
	{
		DestroyDraggableActor();
	}
}

void ADraggableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Draggable && LastDragCharacter != OtherActor)
	{


	}
}

void ADraggableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// This function is called when the actor stops overlapping with 'OtherActor'
	// You can perform actions related to the end of overlap here
}

void ADraggableActor::DestroyDraggableActor()
{
	TriggerDestroyEffects(true);
	Destroy();
}

void ADraggableActor::TriggerDragEffects(AGameCharacter* ByCharacter, bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && DragParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			DragParticles,
			(GetActorLocation() + DragParticlesLocation),
			GetActorRotation()
		);
	}
	if (ByCharacter && DragCharacterParticles)
	{
		FName ParticleComponentName = ActorName.IsEmpty() ? FName(TEXT("DraggableActorParticles")) : FName(*ActorName + FString(" DraggableActorParticles"));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			DragCharacterParticles,
			ByCharacter->GetRootComponent(),
			ParticleComponentName,
			DragCharacterParticlesLocation,
			FRotator(0.0f, 0.0f, 0.0f),
			EAttachLocation::KeepRelativeOffset,
			true
		);
	}
	if (PlaySound && DragSoundComponent) {
		if (!DragSoundComponent->IsPlaying())
		{
			DragSoundComponent->Play();
		}
	}
}


void ADraggableActor::TriggerDropEffects(AGameCharacter* ByCharacter, bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && DropParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			DropParticles,
			(GetActorLocation() + DropParticlesLocation),
			GetActorRotation()
		);
	}
	if (ByCharacter && DropCharacterParticles)
	{
		FName ParticleComponentName = ActorName.IsEmpty() ? FName(TEXT("DraggableActorParticles")) : FName(*ActorName + FString(" DraggableActorParticles"));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			DropCharacterParticles,
			ByCharacter->GetRootComponent(),
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


void ADraggableActor::TriggerThrowEffects(AGameCharacter* ByCharacter, bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && ThrowParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			ThrowParticles,
			(GetActorLocation() + ThrowParticlesLocation),
			GetActorRotation()
		);
	}
	if (ByCharacter && ThrowCharacterParticles)
	{
		FName ParticleComponentName = ActorName.IsEmpty() ? FName(TEXT("DraggableActorParticles")) : FName(*ActorName + FString(" DraggableActorParticles"));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			ThrowCharacterParticles,
			ByCharacter->GetRootComponent(),
			ParticleComponentName,
			ThrowCharacterParticlesLocation,
			FRotator(0.0f, 0.0f, 0.0f),
			EAttachLocation::KeepRelativeOffset,
			true
		);
	}
	if (PlaySound && ThrowSoundComponent) {
		if (!ThrowSoundComponent->IsPlaying())
		{
			ThrowSoundComponent->Play();
		}
	}
}



void ADraggableActor::TriggerHitEffects(AGameCharacter* TargetCharacter, bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && HitParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			HitParticles,
			(GetActorLocation() + HitParticlesLocation),
			GetActorRotation()
		);
	}
	if (TargetCharacter && HitCharacterParticles)
	{
		FName ParticleComponentName = ActorName.IsEmpty() ? FName(TEXT("DraggableActorParticles")) : FName(*ActorName + FString(" DraggableActorParticles"));
		UNiagaraComponent* ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			HitCharacterParticles,
			TargetCharacter->GetRootComponent(),
			ParticleComponentName,
			HitCharacterParticlesLocation,
			FRotator(0.0f, 0.0f, 0.0f),
			EAttachLocation::KeepRelativeOffset,
			true
		);
	}
	if (PlaySound && HitSoundComponent) {
		if (!HitSoundComponent->IsPlaying())
		{
			HitSoundComponent->Play();
		}
	}
}

void ADraggableActor::TriggerDestroyEffects(bool PlaySound)
{
	UWorld* World = GetWorld();
	if (World && DestroyParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			DestroyParticles,
			(GetActorLocation() + DestroyParticlesLocation),
			GetActorRotation()
		);
	}
	if (DestroyParticles && PlaySound && DestroySoundComponent) {
		if (!DestroySoundComponent->IsPlaying())
		{
			DestroySoundComponent->Play();
		}
	}
}
