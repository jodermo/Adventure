#include "Weapon.h"
#include "AdventureCharacter.h"
#include "WeaponProjectile.h"
#include "SpeechBubble.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	InitTool();
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	InitTool();
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitTool();
}

void AWeapon::InitTool()
{
	Super::InitTool();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Character)
	{
		IsSelected = (Character->PrimaryWeapon == this || Character->SecondaryWeapon == this);
		if (Character->NearVehicle || Character->CurrentVehicle)
		{
			Hide();
		}
		else if(Character->PrimaryWeapon == this)
		{
			Show();
		}
	}
	else 
	{
		if (PrimaryCrosshair)
		{
			PrimaryCrosshair->SetActorHiddenInGame(true);
		}
		if (SecondaryCrosshair)
		{
			SecondaryCrosshair->SetActorHiddenInGame(true);
		}
	}
	if (IsSelected && PrimaryAnimationTime > 0.0f)
	{
		PrimaryAnimationTime -= DeltaTime;
		IsPrimaryAttacking = true;
	}
	else {
		PrimaryAnimationTime = 0.0f;
		IsPrimaryAttacking = false;
		if (Character && Character->PrimaryWeapon == this)
		{
			Character->CurrentPrimaryActionAnimation = nullptr;
			Character->StopAllAnimations(Character->PrimaryActionSlot);
		}
	}
	if (IsSelected && SecondaryAnimationTime > 0.0f) 
	{
		PrimaryAnimationTime -= DeltaTime;
		IsSecondaryAttacking = true;
	}
	else 
	{
		SecondaryAnimationTime = 0.0f;
		IsSecondaryAttacking = false;
		if (Character && Character->SecondaryWeapon == this)
		{
			Character->CurrentSecondaryActionAnimation = nullptr;
			Character->StopAllAnimations(Character->SecondaryActionSlot);
		}
	}
	if (Character && IsSelected && CrosshairMesh && HasPrimaryCrosshair && !SecondaryMode)
	{
		if (PrimaryCrosshair) 
		{
			PrimaryCrosshair->AttachToComponent(CrosshairMesh, FAttachmentTransformRules::KeepRelativeTransform);
		}
		if (SecondaryCrosshair) 
		{
			SecondaryCrosshair->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
	else if (Character && CrosshairMesh && HasSecondaryCrosshair && SecondaryMode)
	{
		if (PrimaryCrosshair)
		{
			PrimaryCrosshair->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
		if (SecondaryCrosshair)
		{
			SecondaryCrosshair->AttachToComponent(CrosshairMesh, FAttachmentTransformRules::KeepRelativeTransform);

		}
	}
	else 
	{
		if (PrimaryCrosshair)
		{
			PrimaryCrosshair->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			PrimaryCrosshair->SetActorHiddenInGame(true);
		}
		if (SecondaryCrosshair)
		{
			SecondaryCrosshair->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			SecondaryCrosshair->SetActorHiddenInGame(true);
		}
	}
	if (PrimaryCrosshair)
	{
		PrimaryCrosshair->Character = Character;
	}
	if (SecondaryCrosshair)
	{
		SecondaryCrosshair->Character = Character;
	}
}

void AWeapon::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other,
	UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	// Log("AWeapon NotifyHit: " + GetName() + " <- " + (Other ? Other->GetName() : "None"));
	if (Character && (Character->PrimaryWeapon == this || Character->SecondaryWeapon == this || Character->GetController() == nullptr || Other == Character))
	{
		return;
	}
	AAdventureCharacter* OtherCharacter = Cast<AAdventureCharacter>(Other);
	if (OtherCharacter && Character && OtherCharacter != Character)
	{
		if (IsPrimaryAttacking && PrimaryMeleeDamage != 0.0f) 
		{
			OtherCharacter->TakeDamageAtLocation(PrimaryMeleeDamage, HitLocation, NormalImpulse, this);
		}
		if (IsSecondaryAttacking && SecondaryMeleeDamage != 0.0f) 
		{
			OtherCharacter->TakeDamageAtLocation(SecondaryMeleeDamage, HitLocation, NormalImpulse, this);
		}
	}
	else
	{
		Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	}
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Log("AWeapon OnOverlapBegin: " + GetName() + " <- " + (OtherActor ? OtherActor->GetName() : "None"));
	if (Character && OtherActor != Character) 
	{
		AAdventureCharacter* OtherCharacter = Cast<AAdventureCharacter>(OtherActor);
		FVector HitLocation = SweepResult.ImpactPoint;
		FVector HitNormal = SweepResult.ImpactNormal;
		FVector NormalImpulse = SweepResult.Normal;
		if (OtherCharacter && PrimaryMeleeDamage != 0.0f) 
		{
			OtherCharacter->TakeDamageAtLocation(PrimaryMeleeDamage, HitLocation, NormalImpulse, this);
		}
		if (OtherCharacter && SecondaryMeleeDamage != 0.0f) 
		{
			OtherCharacter->TakeDamageAtLocation(SecondaryMeleeDamage, HitLocation, NormalImpulse, this);
		}
	}
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

FVector AWeapon::GetAimLocation()
{
	FVector StartLocation = GetMuzzleLocation();
	FVector EndLocation;
	if (Character)
	{
		if (!AimFromCWeaponLocation)
		{
			StartLocation = Character->GetActorLocation();
		}
		if (Character->EgoView)
		{
			if (Character->CurrentCameraComponent)
			{
				FVector CameraLocation = Character->CurrentCameraComponent->GetComponentLocation();
				FVector CameraForwardVector = Character->CurrentCameraComponent->GetForwardVector();
				EndLocation = CameraLocation + (CameraForwardVector * EgoViewCrosshairDistance);
			}
		}
		else if (Character->ThirdPersonView)
		{

			FVector CharacterLocation = Character->GetActorLocation();
			FRotator CharacterRotation = Character->GetActorRotation();
			FVector CharacterForwardVector = CharacterRotation.Vector();
			float ScaleFactor = (ThirdPersonViewCrosshairDistance / CharacterForwardVector.Size()) / 1000;
			FVector CameraForwardVector = Character->CurrentCameraComponent->GetForwardVector() + (CharacterForwardVector * ScaleFactor);
			EndLocation = CharacterLocation + (CameraForwardVector * ScaleFactor * ThirdPersonViewCrosshairDistance);
		}
		else if (Character->MapView)
		{
			EndLocation = StartLocation + (Character->GetActorForwardVector() * MapViewCrosshairDistance);
		}
		else
		{
			EndLocation = StartLocation + (Character->GetActorForwardVector() * TopDownViewCrosshairDistance);
		}
		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this); 
		TraceParams.AddIgnoredActor(Character);
		 if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldDynamic, TraceParams))
		{
			return HitResult.ImpactPoint;
		}
	}
	return EndLocation;
}

FVector AWeapon::GetMuzzleLocation()
{
	FVector RelativeSpawnLocation = GetActorRotation().RotateVector(PrimaryMussleOffset);
	return GetActorLocation() + RelativeSpawnLocation;
}

void AWeapon::SetPrimaryMode(bool PrimaryActionMode)
{
	SecondaryMode = !PrimaryActionMode;
}

void AWeapon::Action(bool SecondaryActionMode)
{
	SetPrimaryMode(!SecondaryActionMode);
	if (SecondaryActionMode)
	{
		SecondaryAction();
	}
	else {
		PrimaryAction();
	}
}

void AWeapon::PrimaryAction()
{
	if (Character == nullptr || Character->GetController() == nullptr || Character->PrimaryWeapon != this || Character->NearVehicle || Character->CurrentVehicle)
	{
		return;
	}
	FVector SpawnLocation = GetMuzzleLocation();
	FVector TargetLocation = GetAimLocation();
	FVector DirectionToTarget = (TargetLocation - SpawnLocation).GetSafeNormal();
	FRotator RotationToTarget = DirectionToTarget.Rotation();
	if (PrimaryProjectileClass != nullptr && PrimaryProjectileClass.Get())
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{	
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			AWeaponProjectile* Projectile = World->SpawnActor<AWeaponProjectile>(PrimaryProjectileClass, SpawnLocation, RotationToTarget, ActorSpawnParams);
			if (Projectile)
			{
				Projectile->Weapon = this;
			}
			else 
			{
				return;
			}
		}
	}
	if (PrimaryActionSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PrimaryActionSound, SpawnLocation);
	}
	if (Mesh && PrimaryActionAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(PrimaryActionAnimation, FName("ActionSlot"), 0.f, 0.f, PrimaryActionAnimationRate);
		}
	}
	if (Character && PrimaryActionCharacterAnimation != nullptr)
	{
		if (Character->AnimInstance != nullptr)
		{
			float FadeTime = Character->AnimationFadeInTime + Character->AnimationFadeOutTime;
			Character->StopAllAnimations(Character->PrimaryActionSlot);
			Character->CurrentPrimaryActionAnimation = PrimaryActionCharacterAnimation;
			Character->CurrentPrimaryActionAnimationRate = PrimaryActionCharacterAnimationRate;
			PrimaryAnimationTime = (PrimaryActionCharacterAnimation->GetPlayLength() / PrimaryActionCharacterAnimationRate) - FadeTime;
		}
	}
	if (PrimaryMeleeDamage != 0.0f)
	{
		SetMeleeCollisions(true);
	}
	if (PrimaryActionSpeechBubbleClass && !PrimaryActionSpeechBubbleText.IsEmpty()) {
		ShowPrimaryActionSpeechBubble(PrimaryActionSpeechBubbleText, PrimaryActionSpeechBubbleFontSize, PrimaryActionSpeechBubbleDuration, Character);
	}
	OnPrimaryAction();
}

void AWeapon::SecondaryAction()
{
	if (Character == nullptr || Character->GetController() == nullptr || Character->SecondaryWeapon != this || Character->NearVehicle || Character->CurrentVehicle)
	{
		return;
	}
	FVector SpawnLocation = GetMuzzleLocation();
	FVector TargetLocation = GetAimLocation();
	FVector DirectionToTarget = (TargetLocation - SpawnLocation).GetSafeNormal();
	FRotator RotationToTarget = DirectionToTarget.Rotation();
	if (SecondaryProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			World->SpawnActor<AWeaponProjectile>(SecondaryProjectileClass, SpawnLocation, RotationToTarget, ActorSpawnParams);
		}
	}
	if (SecondaryActionSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SecondaryActionSound, SpawnLocation);
	}
	if (Mesh && SecondaryActionAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(SecondaryActionAnimation, FName("ActionSlot"), 0.f, 0.f, SecondaryActionAnimationRate);
		}
	}
	if (Character && SecondaryActionCharacterAnimation != nullptr)
	{
		if (Character->AnimInstance != nullptr)
		{
			float FadeTime = Character->AnimationFadeInTime + Character->AnimationFadeOutTime;
			Character->StopAllAnimations(Character->SecondaryActionSlot);
			Character->CurrentSecondaryActionAnimation = SecondaryActionCharacterAnimation;
			Character->CurrentSecondaryActionAnimationRate = SecondaryActionCharacterAnimationRate;
			SecondaryAnimationTime = (SecondaryActionCharacterAnimation->GetPlayLength() / SecondaryActionCharacterAnimationRate) - FadeTime;
		}
	}
	if (SecondaryMeleeDamage != 0.0f) 
	{
		SetMeleeCollisions(true);
	}
	if (SecondaryActionSpeechBubbleClass && !SecondaryActionSpeechBubbleText.IsEmpty()) {
		ShowSecondaryActionSpeechBubble(SecondaryActionSpeechBubbleText, SecondaryActionSpeechBubbleFontSize, SecondaryActionSpeechBubbleDuration, Character);
	}
	OnSecondaryAction();
}

void AWeapon::Show()
{
	Super::Show();
	if (Character)
	{
		Character->SelectPrimaryWeapon(this);
		if (PrimaryCrosshair)
		{
			PrimaryCrosshair->SetActorHiddenInGame(false);
		}
		if (SecondaryCrosshair)
		{
			SecondaryCrosshair->SetActorHiddenInGame(false);
		}
		SetMeleeCollisions(true);
	}
}

void AWeapon::Hide()
{
	Super::Hide();
	if (PrimaryCrosshair)
	{
		PrimaryCrosshair->SetActorHiddenInGame(true);
	}
	if (SecondaryCrosshair)
	{
		SecondaryCrosshair->SetActorHiddenInGame(true);
	}
	if (Character)
	{
		SetMeleeCollisions(false);
	}
}

void AWeapon::Use()
{
	if (Character)
	{
		Character->SelectPrimaryWeapon(this);
	}
}

void AWeapon::Drop()
{
	if (Character)
	{
		SetMeleeCollisions(false);
	}
	Super::Drop();
}

void AWeapon::PickedUpByCharacter(AAdventureCharacter* TargetCharacter, bool AsPrimaryWeapon, FName SlotName)
{
	if (TargetCharacter) {
		SlotName = GetCharacterItemSlot(TargetCharacter, false);
		if (SlotName == TargetCharacter->SecondaryWeaponSlot) {
			AsPrimaryWeapon = false;
		}
		else 
		{
			AsPrimaryWeapon = true;
		}
		Super::PickedUpByCharacter(TargetCharacter, AsPrimaryWeapon, SlotName);
		AttachWeapon(Character, AsPrimaryWeapon, SlotName);
		SetMeleeCollisions(true);
	}

}

void AWeapon::AttachWeapon(AAdventureCharacter* TargetCharacter, bool AsPrimaryWeapon, FName SlotName)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}
	UPrimitiveComponent* CharacterPrimitive = Character->FindComponentByClass<UPrimitiveComponent>();
	if (CharacterPrimitive)
	{
		CharacterPrimitive->IgnoreActorWhenMoving(this, true);
	}
	UPrimitiveComponent* ActorPrimitive = FindComponentByClass<UPrimitiveComponent>();
	if (ActorPrimitive)
	{
		ActorPrimitive->IgnoreActorWhenMoving(Character, true);
	}
	if (AsPrimaryWeapon)
	{
		AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SlotName);
		Character->SelectPrimaryWeapon(this);

	}
	else 
	{
		AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SlotName);
		Character->SelectSecondaryWeapon(this);
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ActionMappingContext, 1);
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(PrimaryActionInput, ETriggerEvent::Triggered, this, &AWeapon::PrimaryAction);
		}
	}
}

void AWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(ActionMappingContext);
		}
	}
}

void AWeapon::SetMeleeCollisions(bool CollisionsEnabled)
{
	if ((PrimaryMeleeDamage == 0.0f && SecondaryMeleeDamage == 0.0f ) || !Mesh)
	{
		return;
	}
	CollisionsAreEnabled = CollisionsEnabled;
	if (CollisionsEnabled)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
		Mesh->SetGenerateOverlapEvents(true);
		SetActorEnableCollision(true);
	}
	else
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Mesh->SetGenerateOverlapEvents(false);
		SetActorEnableCollision(false);
	}
}

void AWeapon::ShowPrimaryActionSpeechBubble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter)
{
	TSubclassOf<ASpeechBubble>* UseSpeechBubbleClass = nullptr;

	if (GameMode) {
		if (PrimaryActionSpeechBubble) {
			PrimaryActionSpeechBubble->Hide();
		}
		PrimaryActionSpeechBubble = GameMode->AddSpeechBubble(
			FText::FromString(Text),
			FontSize,
			Duration,
			&PrimaryActionSpeechBubbleLocation,
			new FRotator(0.0f, 90.0f, 0.0f),
			new FVector(1.0f, 1.0f, 1.0f),
			this,
			TargetCharacter,
			&PrimaryActionSpeechBubbleClass
		);
		if (PrimaryActionSpeechBubble)
		{
			PrimaryActionSpeechBubble->Item = this;
		}
	}
}

void AWeapon::ShowSecondaryActionSpeechBubble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter)
{
	if (GameMode) {
		if (SecondaryActionSpeechBubble) {
			SecondaryActionSpeechBubble->Hide();
		}
		SecondaryActionSpeechBubble = GameMode->AddSpeechBubble(
			FText::FromString(Text),
			FontSize,
			Duration,
			&SecondaryActionSpeechBubbleLocation,
			new FRotator(0.0f, 90.0f, 0.0f),
			new FVector(1.0f, 1.0f, 1.0f),
			this,
			TargetCharacter,
			&SecondaryActionSpeechBubbleClass
		);
		if (SecondaryActionSpeechBubble)
		{
			SecondaryActionSpeechBubble->Item = this;
		}
	}
}


void AWeapon::OnPrimaryAction_Implementation()
{
	// can be overwitten by blueprint
}

void AWeapon::OnSecondaryAction_Implementation()
{
	// can be overwitten by blueprint
}