#include "GameCharacter.h"
#include "Components/SkinnedMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/TransformNonVectorized.h"

AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    MouthMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MouthMesh"));
    MouthMesh->SetupAttachment(RootComponent);

    RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
    RightHandMesh->SetOnlyOwnerSee(true);
    RightHandMesh->SetupAttachment(RootComponent);
    RightHandMesh->bCastDynamicShadow = false;
    RightHandMesh->CastShadow = false;
    RightHandMesh->SetRelativeRotation(RightHandMeshRotation);
    RightHandMesh->SetRelativeLocation(RightHandMeshLocation);
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    GetCapsuleComponent()->InitCapsuleSize(CapsuleSize.X, CapsuleSize.Y);
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, RotationRate, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    CharacterWidget = CreateDefaultSubobject<UCharacterWidget>(TEXT("CharacterWidget"));
    CharacterWidget->SetupAttachment(RootComponent);
    CharacterWidget->SetRelativeLocation(CharacterWidgetLocation);
    CharacterWidget->Character = this;


    AudioAnalyser = CreateDefaultSubobject<UAudioAnalyserComponent>(TEXT("AudioAnalyser"));
    AudioAnalyser->Character = this;

	InitCharacter();
}

void AGameCharacter::Log(FString LogMessage) {
    GEngine->AddOnScreenDebugMessage(LogKey, LogTime, LogColor, LogMessage);
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
    AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
    GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
    InitCharacter();
    if (CharacterWidget) 
    {
        CharacterWidget->Character = this;
    }
    AudioAnalyser->Character = this;

}

void AGameCharacter::OnConstruction(const FTransform& Transform)
{
    InitCharacter();
}

void AGameCharacter::InitCharacter()
{
    RootPrimitive = Cast<UPrimitiveComponent>(GetRootComponent());
	if (!AnimInstance && GetMesh())
    {
		AnimInstance = GetMesh()->GetAnimInstance();
	}
    RightHandMesh->SetRelativeRotation(RightHandMeshRotation);
    RightHandMesh->SetRelativeLocation(RightHandMeshLocation);
}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!AnimInstance)
    {
        AnimInstance = GetMesh()->GetAnimInstance();
    }
    FVector Velocity = GetVelocity();
    FVector ForwardVector = GetActorForwardVector();
    CurrentSpeed = (Velocity * ForwardVector).Size();
    SetMovementAnimation(DeltaTime);
	UpdateAnimationStates(DeltaTime);
    CheckStill(DeltaTime);
    if (CharacterWidget)
    {
        CharacterWidget->SetRelativeLocation(CharacterWidgetLocation);
    }

    
}

void AGameCharacter::SetMovementAnimation(float DeltaTime)
{
    bool IsWalking = GetCharacterMovement()->IsWalking();
    if (!AnimInstance) 
    {
        return;
    }
    if (CurrentSpeed == 0.0f)
    {
        CurrentMovementAnimationRate = IdleAnimationRate;
        if (CurrentMovementAnimation != IdleAnimation)
        {
            StopAllAnimations(MovementAnimationSlot);
            CurrentMovementAnimation = IdleAnimation;
        }
    }
    else
    {
        if (IsWalking && IsSprinting)
        {
            CurrentMovementAnimationRate = FMath::Abs(SprintAnimationRate * (CurrentSpeed * AnimationMovementSpeedFactor));
            if (CurrentMovementAnimation != SprintAnimation)
            {
                StopAllAnimations(MovementAnimationSlot);
                CurrentMovementAnimation = SprintAnimation;
            }
        }
        else if (IsWalking && IsCrouching)
        {
            CurrentMovementAnimationRate = FMath::Abs(CrouchAnimationRate * (CurrentSpeed * AnimationMovementSpeedFactor));
            if (CurrentMovementAnimation != CrouchAnimation)
            {
                StopAllAnimations(MovementAnimationSlot);
                CurrentMovementAnimation = CrouchAnimation;
            }
        }
        else if(IsWalking)
        {
            CurrentMovementAnimationRate = FMath::Abs(WalkingAnimationRate * (CurrentSpeed * AnimationMovementSpeedFactor));
            if (CurrentMovementAnimation != WalkingAnimation)
            {
                StopAllAnimations(MovementAnimationSlot);
                CurrentMovementAnimation = WalkingAnimation;
            }
        }
        else
        {
            CurrentMovementAnimationRate = FMath::Abs(FallAnimationnRate * (CurrentSpeed * AnimationMovementSpeedFactor));
            if (CurrentMovementAnimation != FallAnimation)
            {
                StopAllAnimations(MovementAnimationSlot);
                CurrentMovementAnimation = FallAnimation;
            }
        }
    }
}

void AGameCharacter::UpdateAnimationStates(float DeltaTime)
{
    if (!IsDead && CurrentDefaultAnimation)
    {
        UpdateAnimationState(DefaultAnimationSlot, CurrentDefaultAnimation, CurrentDefaultAnimationRate, DeltaTime);
    }
    if (!IsDead && CurrentMovementAnimation)
    {
        UpdateAnimationState(MovementAnimationSlot, CurrentMovementAnimation, CurrentMovementAnimationRate, DeltaTime);
    }
    if (!IsDead && CurrentPrimaryActionAnimation)
    {
        UpdateAnimationState(PrimaryActionSlot, CurrentPrimaryActionAnimation, CurrentPrimaryActionAnimationRate, DeltaTime);
    }
    if (!IsDead && CurrentSecondaryActionAnimation)
    {
        UpdateAnimationState(SecondaryActionSlot, CurrentSecondaryActionAnimation, CurrentSecondaryActionAnimationRate, DeltaTime);
    }
}

void AGameCharacter::UpdateAnimationState(FName AnimationSlot, UAnimSequence* AnimSequence, float AnimationRate, float DeltaTime)
{
    if (!AnimInstance || !AnimSequence)
    {
        return;
    }
    float ActualAnimationRate = (CurrentSpeed < 0) ? -FMath::Abs(AnimationRate) : FMath::Abs(AnimationRate);
    if (!AnimInstance->IsPlayingSlotAnimation(AnimSequence, AnimationSlot))
    {
        UAnimMontage* AnimMontage = AnimInstance->PlaySlotAnimationAsDynamicMontage(AnimSequence, AnimationSlot, AnimationFadeInTime, AnimationFadeOutTime, AnimationRate);
        if (AnimMontage) {
            // AnimInstance->Montage_SetPlayRate(AnimMontage, AnimationRate);
        }
    }

    FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveMontageInstance();
    if (MontageInstance)
    {
        if (!AnimInstance->Montage_IsPlaying(MontageInstance->Montage))
        {
           // AnimInstance->Montage_Play(MontageInstance->Montage, AnimationRate);
        }
        AnimInstance->Montage_SetPlayRate(MontageInstance->Montage, AnimationRate);
    }
}

void AGameCharacter::StopAllAnimations(FName AnimationSlot)
{
    if (AnimInstance)
    {
        // AnimInstance->StopSlotAnimation(AnimationFadeOutTime, AnimationSlot);
    }
}

void AGameCharacter::Die()
{
    IsDead = true;
    SetPhysicsOnly(true);
    GameOver();
}

void AGameCharacter::GameOver()
{
    if (!IsPlayer)
    {
        // Destroy();
        return;
    }
    if (GameMode)
    {
        int AllCharacters = GameMode->Players.Num();
        int CharactersEnded = GameMode->WinnerCharacters.Num() + GameMode->LooserCharacters.Num();
        bool GameIsOver = (AllCharacters == CharactersEnded + 1) ? true : GameOverIfLost;
        GameMode->GameOver(this, GameIsOver);
        SetActorHiddenInGame(true);
        return;
    }
}

void AGameCharacter::WinGame()
{
    if (GameMode)
    {
        int AllCharacters = GameMode->Players.Num();
        int CharactersEnded = GameMode->WinnerCharacters.Num() + GameMode->LooserCharacters.Num();
        bool GameIsOver = (AllCharacters == CharactersEnded + 1) ? true:   GameOverIfLost;
        GameMode->WinGame(this, GameIsOver);
        SetActorHiddenInGame(true);
        return;
    }
}

void AGameCharacter::StopAnimation(UAnimSequence* AnimSequence)
{
    if (AnimInstance && AnimSequence)
    {
        AnimInstance->StopSlotAnimation(AnimationFadeOutTime, DefaultAnimationSlot);
    }
}

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AGameCharacter::ImpulseAtLocation(FVector Impulse, FVector ImpulseLocation)
{

    // GetCharacterMovement()->AddImpulse(Impulse, true);

    SetPhysicsOnly(true);
    InitialVelocity = GetVelocity();
    IsThrown = true;
    if (RootPrimitive)
    {
       // RootPrimitive->AddImpulseAtLocation(Impulse, ImpulseLocation);
    }
    else
    {
      // GetCharacterMovement()->AddImpulse(Impulse, true);

    }
    GetCapsuleComponent()->SetSimulatePhysics(true);
    if (GetCapsuleComponent()->IsSimulatingPhysics()) 
    {
        GetCapsuleComponent()->AddImpulseAtLocation(Impulse, GetActorLocation());
    }
   


}

void AGameCharacter::CheckStill(float DeltaSeconds)
{
    if (IsThrown)
    {
        if (!IsPhysicsOnly) {
            SetPhysicsOnly(true);
        }
        FVector Velocity = GetVelocity();
        if (Velocity.Size() > 0.0f && Velocity.Size() < VelocityTolerance)
        {
            RevertToNormal();
        }
    }
}

void AGameCharacter::RevertToNormal()
{
    IsThrown = false;
    if (!IsDead)
    {
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        FRotator CurrentRotation = GetActorRotation();
        FRotator UprightRotation = FRotator(0, CurrentRotation.Yaw, 0);
        SetActorRotation(UprightRotation);
        FVector CurrentLocation = GetActorLocation();
        FVector RaisedLocation = CurrentLocation + FVector(0, 0, 10);
        SetActorLocation(RaisedLocation);
        SetPhysicsOnly(false);
    }
}

void AGameCharacter::SetPhysicsOnly(bool PhysicsOnly)
{
    if (PhysicsOnly && !IsPhysicsOnly)
    {
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
        GetCharacterMovement()->DisableMovement();
        GetCharacterMovement()->StopMovementImmediately();
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling); // MOVE_None, MOVE_Falling, MOVE_Flying
        GetCapsuleComponent()->SetSimulatePhysics(true);
        if (RootPrimitive)
        {
            RootPrimitive->SetSimulatePhysics(true);
        }
        IsPhysicsOnly = true;
    }
    else if (!PhysicsOnly && IsPhysicsOnly && !IsDead)
    {
        if (RootPrimitive)
        {
            RootPrimitive->SetSimulatePhysics(false);
        }
        GetCapsuleComponent()->SetSimulatePhysics(false);
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    }
}

float AGameCharacter::ReceiveDamage(float DamageAmount)
{
    if (Armor > 0.0f)
    {
        Armor -= DamageAmount;
        if (Armor <= 0.0f)
        {
            Health += Armor;
            Armor = 0.0f;
        }
    }
    else
    {
        Health -= DamageAmount;
    }
    if (Health <= 0.0f)
    {
        Health = 0.0f;
        Die();
    }

    return DamageAmount;
}

float AGameCharacter::TakeDamageAtLocation(float DamageAmount, FVector HitLocation, FVector ImpulseVelocity, AActor* OtherActor)
{
    ImpulseAtLocation(ImpulseVelocity, HitLocation);
    ReceiveDamage(DamageAmount);
    return DamageAmount;
}
