#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Vehicle.h"
#include "AdventureGameModeBase.h"
#include "CharacterWidget.h"
#include "SpeechBubble.h"
#include "AudioAnalyserComponent.h"
#include "NiagaraSystem.h"
#include "DraggableActor.h"
#include "GameCharacter.generated.h"




UCLASS(Blueprintable)
class ADVENTURE_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGameCharacter();

	AAdventureGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = ""))
	ULocalPlayer* LocalPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = ""))
	UPrimitiveComponent* RootPrimitive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Logging", meta = (ToolTip = "Key for character logging"))
	int32 LogKey = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Logging", meta = (ToolTip = "Color for character logging messages"))
	FColor LogColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Logging", meta = (ToolTip = "Time duration for which character logging messages will be displayed"))
	float LogTime = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Log a message related to the character"))
	void Log(FString LogMessage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "CharacterWidget"))
	UCharacterWidget* CharacterWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "AudioAnalyser"))
	UAudioAnalyserComponent* AudioAnalyser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "CharacterWidgetLocation"))
	FVector CharacterWidgetLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Icon for the character"))
	UTexture2D* CharacterIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Name of the character"))
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Description of the character"))
	FString CharacterDescription;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Size of the character's capsule collider in standing position"))
	FVector2D CapsuleSize = FVector2D(42.f, 96.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Size of the character's capsule collider in crouching position"))
	FVector2D CapsuleSizeCrouching = FVector2D(42.f, 48.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "RightHandMesh"))
	USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "RightHandMeshLocation"))
	FVector RightHandMeshLocation = FVector(30.f, 0.f, 60.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "RightHandMeshLocation"))
	FRotator RightHandMeshRotation = FRotator(0.0f, 0.0f, 90.0f);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "GetLeftHandMesh"))
	USkeletalMeshComponent* GetRightHandMesh() const { return RightHandMesh; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MouthMesh"))
	UStaticMeshComponent* MouthMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "LeftHandMesh"))
	USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "LeftHandMeshLocation"))
	FVector LeftHandMeshLocation = FVector(30.f, 0.f, -150.f);

	FRotator LeftHandMeshRotation = FRotator(0.0f, 0.0f, 0.0f);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "GetLeftHandMesh"))
	USkeletalMeshComponent* GetLeftHandMesh() const { return LeftHandMesh; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Speech bubble of the character"))
	ASpeechBubble* SpeechBubble;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the game has started or not."))
	bool IsDead = false;

	// Character Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current health of the character"))
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current armor points of the character"))
	float Armor = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Factor by which armor affects damage taken"))
	float ArmorDamageFactor = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current intelligence level of the character"))
	float Intelligence = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current strength level of the character"))
	float Strength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current points accumulated by the character"))
	int Points = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Points taken away from the character"))
	int TakePoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Current strength level of the character"))
	float Wight = 80.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The current movement speed of the character"))
	float MovementSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Game Character", meta = (ToolTip = "The rate at which the character rotates"))
	float RotationRate = 200.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Animations"))
	float CurrentSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Indicates whether the character is a player"))
	bool IsPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to indicate whether the character attracts NPCs"))
	bool AttractNPC = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Flag to indicate whether the character is currently hidden"))
	bool Hidden = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "If vehicle is near"))
	bool CanMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to indicate whether the character attracts NPCs"))
	bool GameOverIfWon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to indicate whether the character attracts NPCs"))
	bool GameOverIfLost= false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag indicating whether the character is in map view"))
	bool MapView = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag indicating whether the character is in top down view"))
	bool TopDownView = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag indicating whether the character is in ego view"))
	bool EgoView = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag indicating whether the character is in third-person view"))
	bool ThirdPersonView = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Indicates whether the character is currently crouching"))
	bool IsCrouching = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Indicates whether the character is currently sprinting"))
	bool IsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to force the character to sprint regardless of input"))
	bool ForceSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Is true if The character is climbing"))
	bool IsClimbing = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Is true if the character can climb on object"))
	bool IsNearClimbable = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "IsThrown"))
	bool IsThrown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "If inside vehicle"))
	bool InVehicle = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "If vehicle is near"))
	bool NearVehicle = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Closest vehicle"))
	AVehicle* ClosestVehicle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character")
	ADraggableActor* GrabbedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character")
	TArray<ADraggableActor*> NearbyDraggableActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character")
	ADraggableActor* ClosestDraggableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character")
	float DetectDraggableActorRadiusMin = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character")
	float DetectDraggableActorRadiusMax = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character")
	float ThrowDraggableActorForce = 1000.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "LeftHandMeshLocation"))
	FVector ActorDropLocation = FVector(50.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "LeftHandMeshLocation"))
	FVector ActorStartThrowLocation = FVector(50.f, 0.f, 0.f);

	UFUNCTION(BlueprintCallable, Category = "Game Character")
	virtual void GrabClosestActor();

	UFUNCTION(BlueprintCallable, Category = "Game Character")
	virtual void GrabActor(ADraggableActor* DraggableActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character")
	virtual void DropActor();

	UFUNCTION(BlueprintCallable, Category = "Game Character")
	virtual void ThrowActorForward();

	UFUNCTION(BlueprintCallable, Category = "Game Character")
	virtual void ThrowActor(FVector TargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Slots", meta = (ToolTip = "ItemsSlot"))
	FName ItemsSlot = FName("Items");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Slots", meta = (ToolTip = "PrimaryWeaponSlot"))
	FName PrimaryWeaponSlot = FName("PrimaryWeapon");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Slots", meta = (ToolTip = "SecondaryWeaponSlot"))
	FName SecondaryWeaponSlot = FName("SecondaryWeapon");


	UAnimInstance* AnimInstance;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Slots", meta = (ToolTip = "DefaultAnimationSlot"))
	FName DefaultAnimationSlot = FName("DefaultSlot");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Slots", meta = (ToolTip = "MovementAnimationSlot"))
	FName MovementAnimationSlot = FName("Movement");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Slots", meta = (ToolTip = "PrimaryActionSlot"))
	FName PrimaryActionSlot = FName("PrimaryAction");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Slots", meta = (ToolTip = "SecondaryActionSlot"))
	FName SecondaryActionSlot = FName("SecondaryAction");

	UAnimSequence* CurrentDefaultAnimation;
	float CurrentDefaultAnimationRate;

	UAnimSequence* CurrentMovementAnimation;
	float CurrentMovementAnimationRate;

	UAnimSequence* CurrentPrimaryActionAnimation;
	float CurrentPrimaryActionAnimationRate;

	UAnimSequence* CurrentSecondaryActionAnimation;
	float CurrentSecondaryActionAnimationRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float AnimationFadeInTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float AnimationFadeOutTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float AnimationMovementSpeedFactor = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float AnimationEndBufferZone = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float IdleAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* WalkingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float WalkingAnimationRate = 1.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* CrouchAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float CrouchAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* SprintAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float SprintAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* SneakAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float SneakAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* JumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float JumpAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* ClimbingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float ClimbingAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* FallAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float FallAnimationnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* InteractionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float InteractionAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "IdleAnimation"))
	class UAnimSequence* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "Animations"))
	float AttackAnimationRate = 1.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Max distance to detect if vehicle is near"))
	float VelocityTolerance = 250.0f;



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle Effects")
	UNiagaraSystem* GetHitParticles;




	virtual void SetMovementAnimation(float DeltaTime);

	virtual void UpdateAnimationStates(float DeltaTime);
	virtual void UpdateAnimationState(FName AnimationSlot, UAnimSequence* AnimSequence, float AnimationRate, float DeltaTime);
	virtual void StopAnimation(UAnimSequence* AnimSequence);
	virtual void StopAllAnimations(FName AnimationSlot);
	virtual void InitCharacter();
	virtual void DetectClosestActor(float DeltaTime);



	bool IsPhysicsOnly = false;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Called when the character dies"))
	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "GameOver"))
	void GameOver();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Log a message related to the character"))
	void WinGame();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "TakeDamage."))
	virtual float ReceiveDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "TakeDamageAtLocation."))
	virtual float TakeDamageAtLocation(float DamageAmount, FVector HitLocation, FVector ImpulseVelocity, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "ImpulseAtLocation."))
	void ImpulseAtLocation(FVector Impulse, FVector ImpulseLocation);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void RevertToNormal();

	UFUNCTION()
	void CheckStill(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "SetPhysicsOnly"))
	void SetPhysicsOnly(bool PhysicsOnly);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
		FVector InitialVelocity;
};
