#include "AdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "AdventureGameModeBase.h"
#include "Camera/CameraTypes.h"
#include "GenericPlatform/ICursor.h"

AAdventureCharacter::AAdventureCharacter()
{


	Properties = CreateDefaultSubobject<UAdventureCharacterProperties>(TEXT("Properties"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->SetRelativeRotation(FRotator(-TopDownCameraRotationAngle, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	InteractionComponent = CreateDefaultSubobject<UCharacterInteractionComponent>(TEXT("InteractionComponent"));
	InteractionActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractionActorMesh"));
	InteractionActorMesh->SetupAttachment(RootComponent);
	TaskActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TaskActorMesh"));
	TaskActorMesh->SetupAttachment(RootComponent);
	FaceCaptureSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FaceCaptureSpringArm"));
	FaceCaptureSpringArm->SetupAttachment(RootComponent);
	FaceCaptureSpringArm->SetUsingAbsoluteRotation(false);
	FaceCaptureSpringArm->TargetArmLength = FaceCaptureDistance;
	FaceCaptureSpringArm->SetRelativeLocation(EyesLocation);
	FaceCaptureSpringArm->SetRelativeRotation(FaceCaptureRotation);
	FaceCaptureSpringArm->bDoCollisionTest = false;
	FaceCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FaceCaptureComponent"));
	FaceCaptureComponent->SetupAttachment(FaceCaptureSpringArm, USpringArmComponent::SocketName);
	FaceCaptureComponent->SetRelativeLocation(FaceCapturePosition);
	MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMapSpringArm"));
	MiniMapSpringArm->SetupAttachment(RootComponent);
	MiniMapSpringArm->SetUsingAbsoluteRotation(true);
	MiniMapSpringArm->TargetArmLength = MiniMapCameraDistance;
	MiniMapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.f, 0.f));
	MiniMapSpringArm->bDoCollisionTest = false;
	MiniMapSceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapSceneCaptureComponent"));
	MiniMapSceneCaptureComponent->SetupAttachment(MiniMapSpringArm, USpringArmComponent::SocketName);
	MiniMapSceneCaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	MiniMapSceneCaptureComponent->OrthoWidth = MiniMapCameraOrthoWidth;
	MapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MapCameraBoom"));
	MapCameraBoom->SetUsingAbsoluteRotation(true);
	MapCameraBoom->TargetArmLength = MapCameraDistance;
	MapCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MapCamera"));
	MapCameraComponent->SetupAttachment(MapCameraBoom, USpringArmComponent::SocketName);
	NearVehicle = false;
	InVehicle = false;
	CurrentVehicle = nullptr;
	PrimaryCrosshairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrimaryCrosshairMesh"));
	PrimaryCrosshairMesh->SetupAttachment(RootComponent);
	SecondaryCrosshairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryCrosshairMesh"));
	SecondaryCrosshairMesh->SetupAttachment(RootComponent);

	ItemPickUpSpeechComponent = CreateDefaultSubobject<USpeechComponent>(TEXT("ItemPickUpSpeechComponent"));
	ItemPickUpSpeechComponent->Character = this;
	
}

void AAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();
	FollowingCharacters.Empty();
	if (GameMode) {
		GameMode->Characters.Add(this);
		GameMode->AttachMapCamera(MapCameraBoom);
	}
	ItemPickUpSpeechComponent->Character = this;
}

void AAdventureCharacter::InitCharacter() 
{
	GetCapsuleComponent()->SetCapsuleSize(CapsuleSize.X, CapsuleSize.Y, true);
	GetCharacterMovement()->RotationRate = FRotator(0.f, RotationRate, 0.f);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerCharacter = Cast<AAdventureCharacter>(PlayerPawn);
	CharacterController = Cast<AAdventurePlayerController>(Controller);

	if (PlayerCharacter && PlayerCharacter->CharacterController)
	{
		PlayerController = dynamic_cast<AAdventurePlayerController*>(PlayerCharacter->CharacterController);
	}
	UpdateCameraPosition(0.0f);
	SetTopDownView();
	UpdateFaceCapture(0.0f);
}

void AAdventureCharacter::ZoomCamera(float ZoomInput)
{
	if (!EgoView && !ThirdPersonView)
	{
		if (TopDownView) {
			TopDownCameraDistance = CameraBoom->TargetArmLength - ZoomInput;
			TopDownCameraDistance = FMath::Clamp(TopDownCameraDistance, MinCameraDistance, MaxCameraDistance);
		}
		else if (MapView) 
		{
			MapCameraDistance = MapCameraBoom->TargetArmLength - ZoomInput;
			MapCameraDistance = FMath::Clamp(MapCameraDistance, MinCameraDistance, MaxCameraDistance);
		}
	}
}

void AAdventureCharacter::Tick(float DeltaTime)
{

	CanMove = CharacterCanMove();

    Super::Tick(DeltaTime);



	if (!CurrentVehicle && !IsThrown)
	{
		if (CanMove) {
			MovementSpeed = IsCrouching ? (ForceSprinting || IsSprinting) ? CrouchSprintSpeed : CrouchSpeed : (ForceSprinting || IsSprinting) ? SprintSpeed : WalkSpeed;
		}
		else {
			MovementSpeed = 0.0f;
		}
		GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
		UpdateAttributes();
		CheckNearClimbable();
		GetClosestVehicle();
	}


	if (IsPlayer)
	{
		if (CanMove && PlayerController && FMath::Abs(PlayerController->InputComponent->GetAxisValue("Zoom")) > 0.0f)
		{
			float ZoomInput = PlayerController->InputComponent->GetAxisValue("Zoom");
			ZoomCamera(ZoomInput * ZoomSpeed * DeltaTime);
		}
		UpdateCameraPosition(DeltaTime);
		UpdateGameInputState(DeltaTime);
	}
	CameraComponent->SetActive(CurrentCameraComponent == CameraComponent);
	MapCameraComponent->SetActive(CurrentCameraComponent == MapCameraComponent);
	if (NavigationMesh)
	{
		NavigationMesh->SetActorLocation(GetActorLocation());
	}
	UpdateFaceCapture(DeltaTime);
	UpdateCrosshairMesh(DeltaTime);

}
bool AAdventureCharacter::CharacterCanMove()
{
	return !(
		(PrimaryWeapon && (PrimaryWeapon->IsPrimaryAttacking || PrimaryWeapon->IsSecondaryAttacking)) ||
		(SecondaryWeapon && (SecondaryWeapon->IsPrimaryAttacking || SecondaryWeapon->IsSecondaryAttacking))
		);
}

bool AAdventureCharacter::CharacterCanAttack()
{
	return (
		CharacterCanInteract()
		);
}

bool AAdventureCharacter::CharacterCanInteract()
{
	return (
		true
		);
}
void AAdventureCharacter::UpdateCrosshairMesh(float DeltaTime)
{
	if (CurrentVehicle)
	{
		PrimaryCrosshairMesh->SetHiddenInGame(true);
		SecondaryCrosshairMesh->SetHiddenInGame(true);
		return;
	}
	if (PrimaryWeapon)
	{
		PrimaryWeapon->CrosshairMesh = PrimaryCrosshairMesh;
		FVector CrosshairLocation = PrimaryWeapon->GetAimLocation();
		PrimaryCrosshairMesh->SetWorldLocation(CrosshairLocation);
		PrimaryCrosshairMesh->SetHiddenInGame(false);

	}
	else
	{

		PrimaryCrosshairMesh->SetHiddenInGame(true);
	}
	if (SecondaryWeapon)
	{
		SecondaryWeapon->CrosshairMesh = SecondaryCrosshairMesh;
		FVector CrosshairLocation = SecondaryWeapon->GetAimLocation();
		SecondaryCrosshairMesh->SetWorldLocation(CrosshairLocation);
		SecondaryCrosshairMesh->SetHiddenInGame(false);

	}
	else
	{
		SecondaryCrosshairMesh->SetHiddenInGame(true);
	}
}

void AAdventureCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

void AAdventureCharacter::UpdateClimbing(float DeltaTime)
{
	if (IsClimbing && IsNearClimbable)
	{
		FVector ClimbDirection = FVector::ZeroVector;
		float ClimbUpInput = CharacterController->InputComponent->GetAxisValue("ClimbUp");
		float ClimbDownInput = CharacterController->InputComponent->GetAxisValue("ClimbDown");
		ClimbDirection = FVector(0.0f, 0.0f, ClimbUpInput - ClimbDownInput);
		if (!ClimbDirection.IsZero())
		{
			ClimbDirection.Normalize();
		}
		FVector NewLocation = GetActorLocation() + ClimbDirection * ClimbingSpeed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	else if (IsClimbing && !IsNearClimbable)
	{
		StopClimbing();
	}
}

void AAdventureCharacter::CheckNearClimbable()
{
	TArray<FHitResult> HitResults;
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * ClimbCheckDistance);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_GameTraceChannel1, CollisionParams);
	IsNearClimbable = bHit;
}

void AAdventureCharacter::UpdateAttributes()
{
	if (Health <= 0.0f)
	{
		Health = 0.0f;
		Die();
		return;
	}
}

void AAdventureCharacter::SwitchCamera()
{
	if (TopDownView)
	{
		SetThirdPersonView();
	}
	else if (ThirdPersonView)
	{
		SetEgoView();
	}
	else if (EgoView)
	{
		SetMapView();
	}
	else{
		SetTopDownView();
	}
}

void AAdventureCharacter::SetMapView()
{
	SetTopDownView();
	MapView = true;
	TopDownView = false;
	EgoView = false;
	ThirdPersonView = false;
	CanMoveCamera = true;
	MapCameraPosition = GetActorLocation();
	MapCameraBoom->SetRelativeRotation(FRotator(-MapCameraRotationAngle, 0.f, 0.f));
	MapCameraBoom->SetUsingAbsoluteRotation(true);
	MapCameraBoom->bDoCollisionTest = true;
	MapCameraBoom->bEnableCameraLag = true;
	MapCameraComponent->bUsePawnControlRotation = false;
	CurrentCameraComponent = MapCameraComponent;
}

void AAdventureCharacter::SetTopDownView()
{
	StopMoving();
	MapView = false;
	TopDownView = true;
	EgoView = false;
	ThirdPersonView = false;
	CanMoveCamera = false;
	CameraBoom->SetRelativeRotation(FRotator(-TopDownCameraRotationAngle, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->bEnableCameraLag = true;
	CameraComponent->bUsePawnControlRotation = false;
	GetMesh()->SetVisibility(true);
	CurrentCameraComponent = CameraComponent;
}

void AAdventureCharacter::SetThirdPersonView()
{
	StopMoving();
	MapView = false;
	TopDownView = false;
	EgoView = false;
	ThirdPersonView = true;
	CanMoveCamera = false;
	CameraBoom->SetRelativeRotation(FRotator(-ThirdPersonRotationAngle, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->bEnableCameraLag = true;
	CameraComponent->bUsePawnControlRotation = false;
	GetMesh()->SetVisibility(true);
	CurrentCameraComponent = CameraComponent;
}

void AAdventureCharacter::SetEgoView()
{
	StopMoving();
	MapView = false;
	TopDownView = false;
	EgoView = true;
	ThirdPersonView = false;
	CanMoveCamera = false;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = false;
	CameraComponent->bUsePawnControlRotation = false;
	if (HideMeshInEgoView) 
	{
		GetMesh()->SetVisibility(false);
	}
	CurrentCameraComponent = CameraComponent;
}

void AAdventureCharacter::UpdateCameraPosition(float DeltaTime)
{
	if (EgoView)
	{
		CameraDistance = 0.0f;
		ThirdPersonView = false;
		CameraComponent->SetRelativeLocation(EgoCameraOffset + EyesLocation);
	}
	else if (ThirdPersonView && !CurrentVehicle)
	{
		CameraDistance = ThirdPersonCameraDistance;
		CameraComponent->SetRelativeLocation(ThirdPersonCameraOffset);
	}
	else if(!CurrentVehicle)
	{
		CameraDistance = TopDownCameraDistance;
		if (TopDownCameraPosition != FVector::ZeroVector)
		{
			FVector TopDownMapCameraDistance = TopDownCameraPosition - FVector::ZeroVector;
			TopDownCameraPosition -= TopDownMapCameraDistance * DeltaTime;
		}
		CameraComponent->SetRelativeLocation(TopDownCameraOffset + TopDownCameraPosition);
		MapCameraBoom->SetRelativeLocation(MapCameraOffset + MapCameraPosition);
		MapCameraBoom->TargetArmLength = MapCameraDistance;
	}
	if (!CurrentVehicle && CameraBoom->TargetArmLength != CameraDistance)
	{
		if (CameraDistance > CameraBoom->TargetArmLength)
		{
			CameraBoom->TargetArmLength += DeltaTime * ZoomSpeed;
			if (CameraBoom->TargetArmLength > CameraDistance) 
			{
				CameraBoom->TargetArmLength = CameraDistance;
			}
		}
		else if (CameraDistance < CameraBoom->TargetArmLength)
		{
			CameraBoom->TargetArmLength -= DeltaTime * ZoomSpeed;
			if (CameraBoom->TargetArmLength < CameraDistance)
			{
				CameraBoom->TargetArmLength = CameraDistance;
			}
		}
	}
	UpdateCameraRotation(DeltaTime);
}

void AAdventureCharacter::UpdateCameraRotation(float DeltaTime)
{
	if (CurrentVehicle)
	{
		if (!CameraBoomVehicleMode) 
		{
			if (MapView)
			{
				LastCameraMode = FString(TEXT("Map"));
			}
			else if (EgoView)
			{
				LastCameraMode = FString(TEXT("Ego"));
			}
			else if (ThirdPersonView)
			{

				LastCameraMode = FString(TEXT("ThirdPerson"));
			}
			else
			{
				LastCameraMode =  FString(TEXT("TopDown"));
			}
			SetTopDownView();
			FRotator TargetRotation = CurrentVehicle->GetActorRotation();
			FRotator NewCameraRotation = FRotator(-TopDownCameraRotationAngle, 0.0f, 0.0f);
			CameraComponent->SetWorldRotation(NewCameraRotation);
			CameraBoom->SetWorldRotation(TargetRotation);
			CameraBoomVehicleMode = true;
			return;
		}
		CameraBoom->SetUsingAbsoluteRotation(true);
		CameraBoom->bDoCollisionTest = false;
		CameraBoom->bEnableCameraLag = true;
		CameraComponent->bUsePawnControlRotation = false;
		FVector LookAtLocation = CurrentVehicle->GetLookAtLocation();
		FVector CameraRoomLocation = CameraComponent->GetComponentLocation();
		FVector NewCameraRoomLocation = FMath::VInterpTo(CameraRoomLocation, LookAtLocation, DeltaTime, FMath::Clamp(CurrentVehicle->CameraInterpSpeed, 0.1f, 10.0f));
		FRotator TargetRotation = CurrentVehicle->GetActorRotation();
		TargetRotation.Yaw += DeltaTime * CurrentVehicle->CameraSpeed;
		TargetRotation.Pitch += CurrentVehicle->CameraPitchOffset;
		FRotator NewRotation = FMath::RInterpTo(CameraComponent->GetComponentRotation(), TargetRotation, DeltaTime, FMath::Clamp(CurrentVehicle->CameraInterpSpeed, 0.1f, 10.0f));
		CameraBoom->SetWorldRotation(NewRotation);
		float TargetArmLength = CurrentVehicle->DesiredCameraBoomLength; 
		float NewArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, TargetArmLength, DeltaTime, CurrentVehicle->CameraInterpSpeed);
		CameraBoom->TargetArmLength = NewArmLength;
		return;
	}
	else if (CameraBoomVehicleMode)
	{
		if (LastCameraMode == "Map")
		{
			SetMapView();
		}
		else if (LastCameraMode == "ThirdPerson")
		{
			SetThirdPersonView();
		}
		else if (LastCameraMode == "Ego")
		{
			SetEgoView();
		}
		else
		{
			SetTopDownView();
		}
		LastCameraMode = FString(TEXT("None"));
		CameraBoomVehicleMode = false;
		return;
	}
	if (EgoView || ThirdPersonView)
	{
		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		CameraRotation.Pitch = 0.0f;
		CameraRotation.Roll = 0.0f;
		SetActorRotation(CameraRotation);
		if (EgoView)
		{
			float CameraYawInput = PlayerController->InputComponent->GetAxisValue("Turn");
			float CameraPitchInput = PlayerController->InputComponent->GetAxisValue("LookUp");
			FRotator NewCameraRotation = CameraBoom->GetRelativeRotation();
			NewCameraRotation.Yaw += CameraYawInput;
			NewCameraRotation.Pitch = FMath::Clamp(NewCameraRotation.Pitch + CameraPitchInput, -80.f, 80.f);
			CameraBoom->SetRelativeRotation(NewCameraRotation);
		}
		else if (ThirdPersonView)
		{
			FRotator NewCameraRotation = (GetActorLocation() - CameraComponent->GetComponentLocation()).Rotation();
			CameraComponent->SetWorldRotation(NewCameraRotation);
			if (!CurrentVehicle) {
				FRotator NewRotation = CameraBoom->GetComponentRotation();
				NewRotation.Pitch = 0.f;
				NewRotation.Roll = 0.f;
				SetActorRotation(NewRotation);
			}
		}
	}
	else
	{
		if (RotateTopDownWithPlayer)
		{
			FRotator NewCameraRotation = GetActorRotation() + FRotator(-TopDownCameraRotationAngle, 0.0f, 0.0f);
			CameraComponent->SetWorldRotation(NewCameraRotation);
		}
		else
		{
			FRotator NewCameraRotation = FRotator(-TopDownCameraRotationAngle, 0.0f, 0.0f);
			CameraComponent->SetWorldRotation(NewCameraRotation);
		}
	}
}

void AAdventureCharacter::UpdateFaceCapture(float DeltaTime)
{
	if (!IsPlayer && (!CurrentInteractionActor || CurrentInteractionActor != PlayerCharacter->CurrentInteractionActor)) {
		DoCaptureFace = false;
	} 
	else 
	{
		DoCaptureFace = DoCaptureFace;
	}
	if (DoCaptureFace || IsPlayer)
	{
		FaceCaptureComponent->SetActive(true);
	}
	else
	{
		FaceCaptureComponent->SetActive(false);
		return;
	}
}

bool AAdventureCharacter::GUIIsActive()
{
	return  GameMode &&
		(
			(GameMode->MenuVisible || GameMode->InventarVisible || GameMode->GameIsOver) ||
			(MenuVisible || InventarVisible || InteractionVisible)
		);
}

void AAdventureCharacter::UpdateGameInputState(float DeltaTime)
{
	bool GUIActive = GUIIsActive();
	if (!GUIActive)
	{
		if (EgoView)
		{
			CameraBoom->bEnableCameraLag = false;
		}
		else 
		{
			CameraBoom->bEnableCameraLag = true;
		}
		SetGameInputMode(false);
	}
	else
	{
		CameraBoom->bEnableCameraLag = true;
		SetGameInputMode(true);
	}
}

void AAdventureCharacter::SetGameInputMode(bool ShowMouseCursor)
{
	if (PlayerController)
	{
		if (ShowMouseCursor)
		{
			// GUI
			PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableTouchEvents = true;
			PlayerController->bEnableTouchOverEvents = true;
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableTouchOverEvents = true;
			PlayerController->ShouldShowMouseCursor();
			PlayerController->SetShowMouseCursor(true);
			PlayerController->InputEnabled();
			PlayerController->ShouldPerformFullTickWhenPaused();
			PlayerController->UnFreeze();
			PlayerController->EndInactiveState();
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(true);
			PlayerController->SetInputMode(InputMode);
			PlayerController->EnableInput(PlayerController);
		}
		else
		{
			// In Game
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
		    PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableMouseOverEvents = false;
		}
	}
}

void AAdventureCharacter::StartCrouch()
{
	if (CanMove && !CurrentVehicle && !IsThrown)
	{
		if (!IsCrouching)
		{
			IsCrouching = true;
	
			GetCapsuleComponent()->SetCapsuleSize(CapsuleSizeCrouching.X, CapsuleSizeCrouching.Y, true);
		}
	}
}

void AAdventureCharacter::StopCrouch()
{
	if (!CurrentVehicle)
	{
		if (IsCrouching)
		{
			IsCrouching = false;

			GetCapsuleComponent()->SetCapsuleSize(CapsuleSize.X, CapsuleSize.Y, true);
		}
	}
}

void AAdventureCharacter::StartSprint()
{
	if (CanMove && !CurrentVehicle)
	{
		if (!IsSprinting)
		{
			IsSprinting = true;
		}
	}
}

void AAdventureCharacter::StopSprint()
{
	if (!CurrentVehicle)
	{
		if (IsSprinting)
		{
			IsSprinting = false;
			ForceSprinting = false;
		}
	}
}

void AAdventureCharacter::ToggleSprinting()
{
	ForceSprinting = !ForceSprinting;
	if (!ForceSprinting) 
	{
		StopSprint();
	}
	else 
	{
		StartSprint();
	}
}

void AAdventureCharacter::MoveDirection(FVector DirectionVector, float Amount)
{
	if (CanMove) 
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
		AddMovementInput(DirectionVector, MovementSpeed * Amount);
	}

}

void AAdventureCharacter::LookDirection(FVector DirectionVector)
{
	SetActorRotation(DirectionVector.Rotation());
}

void AAdventureCharacter::StopMoving()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	if (PlayerController)
	{
		PlayerController->StopMovement();
	}
}


void AAdventureCharacter::LookUp(float Value)
{
	if (ThirdPersonView || EgoView)
	{
		FRotator NewRotation = CameraBoom->GetRelativeRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - Value, -80.f, 80.f);
		CameraBoom->SetRelativeRotation(NewRotation);
	}
}

void AAdventureCharacter::LookRight(float Value)
{
	if (ThirdPersonView || EgoView)
	{
		FRotator NewRotation = CameraBoom->GetRelativeRotation();
		NewRotation.Yaw += Value;
		CameraBoom->SetRelativeRotation(NewRotation);
	}
}




bool AAdventureCharacter::IsItemCollected(AItemActor* Item)
{
	return CollectedItems.Contains(Item);
}

void AAdventureCharacter::PickupItem(AItemActor* Item, FName SlotName)
{

	if (Item && Item->Collectable)
	{
		Item->PickedUpByCharacter(this, true, SlotName);
		
		if (Item->MakeCharacterUnrecognisable)
		{
			AttractNPC = false;
		}
		if (Item->MakeCharacterRecognisable) 
		{
			AttractNPC = true;
		}
		if (Item->CharacterDieOnPickUp)
		{
			Die();
			return;
		}
		if (IsPlayer && GameMode)
		{
			if (Item->OpenInventarOnPickUp)
			{
				GameMode->ShowInventar();
			}
		}
		if (Item->TriggerInteraction && Item->InteractionActorClass && Item->InteractionActorClass.Get())
		{
			bool AddInteraction = true;
			if (!ItemInteractionActorClasses.Contains(Item->InteractionActorClass))
			{
				ItemInteractionActorClasses.Add(Item->InteractionActorClass);
			}
			else 
			{
				if (Item->TriggerInteractionOnlyOnce)
				{
					AddInteraction = false;
				}
			}
			AInteractionActor* InteractionActor = GetWorld()->SpawnActor<AInteractionActor>(Item->InteractionActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
			InteractionActor->Character = Item->InteractionCharacter ? Item->InteractionCharacter:  this;
			InteractionActor->TargetCharacter = this;
			TriggerInteractionActor(this, InteractionActor);
			if (AddInteraction)
			{
				if (InteractionActor)
				{
					AddInteractionActor(InteractionActor);
					SelectInteractionActor(InteractionActor);
				}
			}
		}
	}
	if (ItemPickUpSpeechComponent) {
		ItemPickUpSpeechComponent->SpeakToCharacter(this);
	}
	OnPickupItem(Item, SlotName);
}



void AAdventureCharacter::OnPickupItem_Implementation(AItemActor* Item, FName SlotName)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::AddItem(AItemActor* Item)
{
	if (Item)
	{
		if (Item->Collectable) 
		{
			if (Item->Stackable)
			{
				AItemActor* FoundItem = nullptr;
				for (AItemActor* CollectedItem : CollectedItems)
				{
					if (CollectedItem && CollectedItem->ItemAlias == Item->ItemAlias)
					{
						FoundItem = CollectedItem;
						break;
					}
				}
				if (FoundItem)
				{
					FoundItem->Stack += Item->Stack;
				}
				else
				{
					if (!CollectedItems.Contains(Item))
					{
						CollectedItems.Add(Item);
					}
				}
			}
			else 
			{
				if (!CollectedItems.Contains(Item))
				{
					CollectedItems.Add(Item);
				}
			}
		}
		ATool* Tool = Cast<ATool>(Item); // TODO: maybe better way then Cast?!
		if (Tool)
		{
			AWeapon* Weapon = Cast<AWeapon>(Tool); // TODO: maybe better way then Cast?!
			if (Weapon && !Weapons.Contains(Weapon))
			{
				Weapons.Add(Weapon);
			}
			else if(!Weapon && !Tools.Contains(Weapon))
			{
				Tools.Add(Tool);
			}
		}
	}
	OnAddItem(Item);

}

void AAdventureCharacter::OnAddItem_Implementation(AItemActor* Item)
{
	// can be overwitten by blueprint
}


void AAdventureCharacter::UseItem(AItemActor* Item)
{
	Item->Use();
	CollectedItems.Remove(Item);
	Item->Destroy();
	OnUseItem(Item);
}

void AAdventureCharacter::OnUseItem_Implementation(AItemActor* Item)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::SelectItem(AItemActor* Item)
{
	if (Item && !SelectedItems.Contains(Item))
	{
		SelectedItems.Add(Item);
	}
}

void AAdventureCharacter::UnselectItem(AItemActor* Item)
{
	if (Item)
	{
		SelectedItems.Remove(Item);
	}
}

bool AAdventureCharacter::IsItemSelected(AItemActor* Item)
{
	return SelectedItems.Contains(Item);
}

void AAdventureCharacter::ToggleSelectItem(AItemActor* Item)
{
	if (IsItemSelected(Item))
	{
		UnselectItem(Item);
	}
	else
	{
		SelectItem(Item);
	}
}

void AAdventureCharacter::SelectTool(ATool* Tool)
{
	if (Tool && !Tools.Contains(Tool))
	{
		Tools.Add(Tool);
	}
	SelectedTool = Tool;
}

void AAdventureCharacter::SelectPrimaryWeapon(AWeapon* Weapon)
{
	if (Weapon && !Weapons.Contains(Weapon))
	{
		Weapons.Add(Weapon);
	}
	if (PrimaryWeapon != Weapon)
	{
		if (PrimaryWeapon) {
			PrimaryWeapon->Hide();
		}
		PrimaryWeapon = Weapon;
		if (PrimaryWeapon) {
			PrimaryWeapon->Show();
		}
	}
}

void AAdventureCharacter::SelectSecondaryWeapon(AWeapon* Weapon)
{
	if (Weapon && !Weapons.Contains(Weapon))
	{
		Weapons.Add(Weapon);
	}
	SecondaryWeapon = Weapon;
}

void AAdventureCharacter::OnAreaOverlapBegin(AAreaActor* AreaActor)
{
	if (AreaActor->CharacterDieOnEnter && GameMode)
	{
		Die();
	}
	if (AreaActor->GameOverOnEnter && GameMode)
	{
		GameOver();
		return;
	}
	if (AreaActor->WinGameOnEnter && GameMode)
	{
		WinGame();
		return;
	}
	if (AreaActor->HideCharacter)
	{
		Hidden = true;
	}
	if (AreaActor->MakeCharacterUnrecognisable)
	{
		AttractNPC = false;
	}
	if (AreaActor->MakeCharacterRecognisable)
	{
		AttractNPC = true;
	}
	if (AreaActor->TriggerInteraction)
	{
		AInteractionActor* NewInteractionActor = GetWorld()->SpawnActor<AInteractionActor>(AreaActor->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		AddInteractionActor(NewInteractionActor);
		SelectInteractionActor(NewInteractionActor);
	}
}

void AAdventureCharacter::OnAreaOverlapEnd(AAreaActor* AreaActor)
{
	if (AreaActor->HideCharacter)
	{
		Hidden = false;
	}
}

void AAdventureCharacter::DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{
	if (InteractionComponent) {
		InteractionComponent->DoCharacterInteraction(TargetCharacter, DeltaTime);
	}
}

void AAdventureCharacter::OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{
	if (InteractionComponent) 
	{
		InteractionComponent->OnCharacterInteraction(TargetCharacter, DeltaTime);
	}
}

void AAdventureCharacter::OnCharacterActorInteraction(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor)
{
	if (InteractionComponent)
	{
		InteractionComponent->OnCharacterActorInteraction(TargetCharacter, InteractionActor, 1.0f);
	}
}

void AAdventureCharacter::MoveForward(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}
	if (CurrentVehicle)
	{
		return;
	}
	FVector ForwardDirection = FVector::ZeroVector;
	if (IsClimbing && IsNearClimbable)
	{
		FVector ClimbDirection = FVector::ZeroVector;
		ClimbDirection = GetActorUpVector();
		ForwardDirection = ClimbDirection + GetActorForwardVector();
	}
	else
	{
		if (EgoView || ThirdPersonView)
		{
			ForwardDirection = CameraComponent->GetForwardVector();
		}
		else
		{
			const FRotator Rotation = CameraComponent->GetComponentRotation();
			ForwardDirection = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		}
	}
	ForwardDirection.Normalize();
	MoveDirection(ForwardDirection, Value);
}

void AAdventureCharacter::DriveForward(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}
	if (CurrentVehicle)
	{
		CurrentVehicle->MoveForward(Value);
		return;
	}
}

void AAdventureCharacter::MoveRight(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}
	if (CurrentVehicle)
	{
		return;
	}
	FVector Direction;
	if (EgoView || ThirdPersonView)
	{
		Direction = CameraComponent->GetRightVector();
	}
	else
	{
		const FRotator Rotation = CameraComponent->GetComponentRotation();
		Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	}
	MoveDirection(Direction, Value);
}

void AAdventureCharacter::DriveRight(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}
	if (CurrentVehicle)
	{
		CurrentVehicle->MoveRight(Value);
		return;
	}
}

void AAdventureCharacter::MoveCameraUp(float Value)
{
	if (TopDownView && CanMoveCamera)
	{

		TopDownCameraPosition += FVector(Value * TopDownMapCameraSpeed, 0.0f, 0.0f);
	}
	else if (MapView && CanMoveCamera)
	{
		MapCameraPosition += FVector(0.0f, 0.0f, Value * TopDownMapCameraSpeed);
	}
}

void AAdventureCharacter::MoveCameraForward(float Value)
{


	if (TopDownView && CanMoveCamera)
	{
		TopDownCameraPosition += FVector(0.0f, 0.0f, Value * TopDownMapCameraSpeed);
	}
	else if (MapView && CanMoveCamera)
	{
		MapCameraPosition += FVector(-Value * TopDownMapCameraSpeed, 0.0f, 0.0f);
	}
}

void AAdventureCharacter::MoveCameraRight(float Value)
{
	if (TopDownView && CanMoveCamera)
	{
		TopDownCameraPosition += FVector(0.0f, Value * TopDownMapCameraSpeed, 0.0f);
	}
	else if (MapView && CanMoveCamera)
	{
		MapCameraPosition += FVector(0.0f, Value * TopDownMapCameraSpeed, 0.0f);
	}
}

void AAdventureCharacter::TriggerInteractionActor(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor)
{
	AAdventureCharacter* Character = this;
	if (!TargetCharacter)
	{
		TargetCharacter = InteractionActor->Character ? InteractionActor->TargetCharacter : Character;
	}
	InteractionActor->Character = Character;
	InteractionActor->TargetCharacter = TargetCharacter;
	if (InteractionActor)
	{
		if (Character != TargetCharacter) {
			Character->CurrentInteractionActor = InteractionActor;
			Character->DoCaptureFace = true;
		}
		if (Character && InteractionActor->IgnoreCharacter)
		{
			Character->IgnoreCharacter(TargetCharacter);
		}
		if (Character && InteractionActor->UnignoreCharacter)
		{
			Character->UnignoreCharacter(TargetCharacter);
		}
		if (InteractionActor->SpeakToActor)
		{
			if (InteractionActor->SpeechComponent)
			{
			
			
				InteractionActor->SpeechComponent->SpeakToCharacter(TargetCharacter);
				// AudioAnalyser->SetAudioComponent(InteractionActor->SpeechAudio.AudioComponent, InteractionActor->SpeechAudio.RhubarbPhonemeData);

				// InteractionActor->SpeechAudio.AudioComponent->Play();

				// InteractionActor->SpeechComponent->ShowSpeechBuuble(InteractionActor->SpeechBubbleText, InteractionActor->ShowSpeechBubbleTextSize, InteractionActor->ShowSpeechBubbleTime);
			}

		}
		if (Character && InteractionActor->MakeDamage && TargetCharacter != Character)
		{
			if (InteractionActor->MakeDamageOnlyOnce && !InteractionActor->DidDamage)
			{
				Character->Attack(TargetCharacter, InteractionActor->DamageMultiplicator, 1.0f);
			}
			else if (!InteractionActor->MakeDamageOnlyOnce)
			{
				Character->Attack(TargetCharacter, InteractionActor->DamageMultiplicator, 1.0f);
			}
		}
		if (InteractionActor->GivePoints)
		{
			if (InteractionActor->GivePointsOnlyOnce && !InteractionActor->AwardedPoints)
			{
				TargetCharacter->AddPoints(InteractionActor->PointsToGive);

				InteractionActor->AwardedPoints = true;
			}
			else if (!InteractionActor->GivePointsOnlyOnce)
			{
				TargetCharacter->AddPoints(InteractionActor->PointsToGive);
				InteractionActor->AwardedPoints = true;
			}
		}
		if (InteractionActor->GiveItems)
		{
			for (TSubclassOf<AItemActor> InteractionItemClass : InteractionActor->InteractionItemClasses)
			{
				AItemActor* InteractionItem = GetWorld()->SpawnActor<AItemActor>(InteractionItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
				InteractionItem->InteractionCharacter = TargetCharacter;
				InteractionItem->Character = this;
				TargetCharacter->PickupItem(InteractionItem, ItemsSlot);
			}
		}
		if (InteractionActor->GiveActor)
		{
			TargetCharacter->AddInteractionActor(InteractionActor);
		}
		if (InteractionActor->TriggerTasks)
		{
			if (InteractionActor->TriggertTaskAfterAnother)
			{
				InteractionActor->TriggerNextTask();
			}
			else {
				for (TSubclassOf<ATaskActor> InteractionTaskClass : InteractionActor->InteractionTaskClasses)
				{
					ATaskActor* NewTaskActor = GetWorld()->SpawnActor<ATaskActor>(InteractionTaskClass, FVector::ZeroVector, FRotator::ZeroRotator);
					NewTaskActor->Character = this;
					NewTaskActor->TargetCharacter = TargetCharacter;
					NewTaskActor->TriggerCharacterTask(TargetCharacter);
				}
			}
		}
		if (InteractionActor->TriggerInteraction && InteractionActor->InteractionActorClass && InteractionActor->InteractionActorClass.Get())
		{
			AInteractionActor* NewInteractionActor = GetWorld()->SpawnActor<AInteractionActor>(InteractionActor->InteractionActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
			NewInteractionActor->Character = this;
			NewInteractionActor->TargetCharacter = TargetCharacter;
			TargetCharacter->AddInteractionActor(NewInteractionActor);
			TargetCharacter->SelectInteractionActor(NewInteractionActor);
		}
		else if (InteractionActor->TriggerInteraction && (!InteractionActor->InteractionActorClass || !InteractionActor->InteractionActorClass.Get()))
		{
			AInteractionActor* NewInteractionActor = GetWorld()->SpawnActor<AInteractionActor>(InteractionActor->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator);
			NewInteractionActor->Character = this;
			NewInteractionActor->TargetCharacter = TargetCharacter;
			TargetCharacter->AddInteractionActor(NewInteractionActor);
			TargetCharacter->SelectInteractionActor(NewInteractionActor);
		}
		else if(!InteractionActor->ShowInteraction)
		{
			TargetCharacter->CloseInteraction();
			if (TargetCharacter->GameMode)
			{
				TargetCharacter->GameMode->CloseInteraction();
			}
		}
		OnCharacterActorInteraction(TargetCharacter, InteractionActor);
	}
}

void AAdventureCharacter::AddInteractionActor(AInteractionActor* InteractionActor)
{
	if (InteractionActor->GiveActor)
	{
		CollectedInteractionActors.Add(InteractionActor);
	}
	if (InteractionActor->AppendActorToCharacter)
	{
		InteractionActor->SetActorEnableCollision(false);
		InteractionActor->SetActorTickEnabled(false);
		InteractionActor->TargetCharacter = this;
		InteractionActor->AttachToComponent(InteractionActorMesh, FAttachmentTransformRules::KeepRelativeTransform);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
	}
	if (InteractionActor->GiveActorAsItem)
	{
		PickupItem(InteractionActor, ItemsSlot);
	}
	if (InteractionActor->ForceInteraction || (InteractionActor->ShowInteraction && !CurrentInteractionActor))
	{
		SelectInteractionActor(InteractionActor);
	}
}

void AAdventureCharacter::RemoveInteractionActor(AInteractionActor* InteractionActor)
{
	CollectedInteractionActors.Remove(InteractionActor);
	InteractionActor->Destroy();
}

void AAdventureCharacter::SelectInteractionActor(AInteractionActor* InteractionActor)
{
	CurrentInteractionActor = InteractionActor;
	if (CurrentInteractionActor->ShowInteractionView) 
	{
		ShowInteraction();
	}
	if (CurrentInteractionActor->ShowInteractionViewToAll) 
	{
		if (GameMode)
		{
			GameMode->ShowInteraction(InteractionActor);
		}
		if (InteractionActor->PauseGame)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayedPause, this, &AAdventureCharacter::PauseGame, .02f, false);
		}
	}

}

void AAdventureCharacter::PauseGame() 
{
	if (GameMode)
	{
		if (CurrentInteractionActor && CurrentInteractionActor->Character && CurrentInteractionActor->Character != this)
		{
			CurrentInteractionActor->Character->DoCaptureFace = false;
		}
		GameMode->PauseGame();
	}
}

void AAdventureCharacter::AddTaskActor(ATaskActor* TaskActor)
{
	if (TaskActor->IsValidLowLevel())
	{
		TaskActor->SetActorEnableCollision(false);
		TaskActor->SetActorTickEnabled(false);
		TaskActor->TargetCharacter = this;
		TaskActor->AttachToComponent(TaskActorMesh, FAttachmentTransformRules::KeepRelativeTransform);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
		SelectTaskActor(TaskActor);
	}
	CollectedTaskActors.Add(TaskActor);
}

void AAdventureCharacter::AddTargetArea(ATaskActor* TaskActor, AAreaActor* AreaActor)
{
	TargetAreas.Add(AreaActor);
}

void AAdventureCharacter::RemoveTaskActor(ATaskActor* TaskActor)
{
	CollectedTaskActors.Remove(TaskActor);
	TaskActor->Destroy();
}

void AAdventureCharacter::SelectTaskActor(ATaskActor* TaskActor)
{
	CurrentTaskActor = TaskActor;
	if (GameMode && CurrentInteractionActor->TriggerTasks) {
		// GameMode->ShowTask(TaskActor);
	}
}

void AAdventureCharacter::Jump()
{
	if (CanMove && !CurrentVehicle)
	{
		if (JumpCount < CanJumpForCount)
		{

			if (JumpCount < 1) {
				Super::Jump();
			}
			else if (CanDoubleJump)
			{
				float JumpZVelocity = sqrt(2 * JumpHeight * JumpGravity);
				LaunchCharacter(FVector(0.0f, 0.0f, JumpZVelocity), false, true);
				Log("DoubleJumpt: " + FString::FromInt(JumpCount));
			}
			else {
				Log("No DoubleJumpt");
			}
			JumpCount++;

		}
	}
}

bool AAdventureCharacter::CanJumpInternal()
{
	bool bCanJump = false;

	if (CanMove && !CurrentVehicle && bCanJump && JumpCount >= CanJumpForCount)
	{
		bCanJump = false;
	}

	return bCanJump;
}

void AAdventureCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	ResetJumpCount();
}

void AAdventureCharacter::ResetJumpCount()
{
	JumpCount = 0;
}

void AAdventureCharacter::Attack(AAdventureCharacter* TargetCharacter, float DamageFactor, float DeltaTime)
{
	if (CharacterCanAttack() && !CurrentVehicle)
	{
		float AttackDamage = GetAttackDamage(TargetCharacter, DamageFactor, DeltaTime);
		if (TargetCharacter->Armor > 0.0f) 
		{
			TargetCharacter->Armor -= AttackDamage * ArmorDamageFactor;
			if (TargetCharacter->Armor < 0.0f)
			{
				TargetCharacter->Armor = 0.0f;
			}
		}
		else 
		{
			TargetCharacter->Health -= AttackDamage;
			if (TargetCharacter->Health < 0.0f)
			{
				TargetCharacter->Health = 0.0f;
			}
		}
	}
}

float AAdventureCharacter::GetAttackDamage(AAdventureCharacter* TargetCharacter, float DamageFactor, float DeltaTime)
{
	return Strength * DamageFactor * DeltaTime / 10;
}

int AAdventureCharacter::AddPoints(int NewPoints)
{
	Points = Points + NewPoints;
	return Points;
}

void AAdventureCharacter::IgnoreCharacter(AAdventureCharacter* CharacterToIgnore)
{
	if (!IgnoreCharacters.Contains(CharacterToIgnore))
	{;
		IgnoreCharacters.Add(CharacterToIgnore);
	}
}

void AAdventureCharacter::UnignoreCharacter(AAdventureCharacter* CharacterToIgnore)
{
	if (IgnoreCharacters.Contains(CharacterToIgnore))
	{
		IgnoreCharacters.Remove(CharacterToIgnore);
	}
}

void AAdventureCharacter::StartClimbing()
{
	if (CanMove && IsNearClimbable)
	{
		GetCharacterMovement()->GravityScale = 0.f;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		IsClimbing = true;
	}
}

void AAdventureCharacter::StopClimbing()
{
	if (IsClimbing)
	{
		GetCharacterMovement()->GravityScale = 1.f;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		IsClimbing = false;
	}
}

void AAdventureCharacter::ShowMenu()
{
	MenuVisible = true;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::CloseMenu()
{
	MenuVisible = false;
	if (GameMode)
	{
		GameMode->ResumeGame();
	}
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::ShowInventar()
{
	InventarVisible = true;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::CloseInventar()
{
	InventarVisible = false;
	if (GameMode)
	{
		GameMode->ResumeGame();
	}
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::ShowControls()
{
	ControlsVisible = true;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::CloseControls()
{
	ControlsVisible = false;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::ShowMap()
{
	MapVisible = true;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::CloseMap()
{
	MapVisible = false;
	if (GameMode)
	{
		GameMode->ResumeGame();
	}
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::ShowInteraction()
{
	InteractionVisible = true;
	UpdateGameInputState(0.0f);
}

void AAdventureCharacter::CloseInteraction()
{
	InteractionVisible = false;
	if (GameMode)
	{
		GameMode->ResumeGame();
	}
	UpdateGameInputState(0.0f);
}

AVehicle* AAdventureCharacter::GetClosestVehicle()
{
	float ClosestDistance = MaxVehicleDistance;
	NearVehicle = false;
	ClosestVehicle = nullptr;
	if (GameMode)
	{
		for (AVehicle* FoundVehicle : GameMode->Vehicles)
		{
			if (FoundVehicle)
			{
				float Distance = FVector::Dist(FoundVehicle->GetActorLocation(), GetActorLocation());
				if (Distance <= MaxVehicleDistance && Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestVehicle = FoundVehicle;
					NearVehicle = true;
					if (!ClosestVehicle->DriverCharacter && !ClosestVehicle->SpeechBubble) 
					{
						ClosestVehicle->ShowSpeechBuuble("Drive me, press \"F\"", 80.0f, 10.0f, this);
					}
				}
			}
		}
		return ClosestVehicle;
	}
	return nullptr;
}

void AAdventureCharacter::ShowSpeechBuuble(FString Text, float FontSize, float Duration)
{
	if (GameMode) {
		if (SpeechBubble) {
			SpeechBubble->Hide();
		}
		SpeechBubble = GameMode->AddSpeechBubble(
			FText::FromString(Text),
			FontSize,
			Duration,
			new FVector(0.0f, -100.0f, 40.0f),
			new FRotator(0.0f, 90.0f, 0.0f),
			new FVector(.5f, .5f, .5f),
			this,
			this,
			nullptr
		);
		if (SpeechBubble)
		{
			SpeechBubble->Character = this;
		}
	}
}

void AAdventureCharacter::EnterVehicle()
{
	if (CanMove && CharacterCanInteract()  && NearVehicle && !InVehicle && ClosestVehicle && !CurrentVehicle)
	{
		InVehicle = true;
		ClosestVehicle->OnEnterVehicle(this);
		if (!SpeechBubble)
		{
			if (ClosestVehicle->SpeechBubble) {
				ClosestVehicle->SpeechBubble->Hide();
			}
			ShowSpeechBuuble("Wow a car!", 80.0f, 5.0f);
		}
	}
}

void AAdventureCharacter::OnEnterVehicle_Implementation(AVehicle* Vehicle)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::ExitVehicle()
{
	if (InVehicle && CurrentVehicle)
	{
		InVehicle = false;
		CurrentVehicle->OnExitVehicle(this);
	}
}


void AAdventureCharacter::OnExitVehicle_Implementation(AVehicle* Vehicle)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::Interact(AActor* Actor)
{
	if (ClosestVehicle && NearVehicle)
	{
		if (!InVehicle)
		{
			EnterVehicle();
		}
		else
		{
			ExitVehicle();
		}
		OnInteract(ClosestVehicle);
		return;
	}
	OnInteract(Actor);
}

void AAdventureCharacter::OnInteract_Implementation(AActor* Actor)
{
	// can be overwitten by blueprint
}


void AAdventureCharacter::PrimaryAction(bool SecondaryActionMode)
{
	if (PrimaryWeapon)
	{
		PrimaryWeapon->Action(SecondaryActionMode);
	}
	OnPrimaryAction(PrimaryWeapon, SecondaryActionMode);
}

void AAdventureCharacter::OnPrimaryAction_Implementation(AWeapon* Weapon, bool SecondaryActionMode)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::SecondaryAction(bool SecondaryActionMode)
{
	if (SecondaryWeapon)
	{
		SecondaryWeapon->Action(SecondaryActionMode);
	}
	OnSecondaryAction(SecondaryWeapon, SecondaryActionMode);
}

void AAdventureCharacter::OnSecondaryAction_Implementation(AWeapon* Weapon, bool SecondaryActionMode)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::UseItems()
{
	if (SelectedItems.Num())
	{
		for (AItemActor* Item : SelectedItems) {
			UseItem(Item);
		}
	}
	OnUseItems(SelectedItems);
}

void AAdventureCharacter::OnUseItems_Implementation(const TArray<AItemActor*>& Items)
{
	// Implementation here
}

void AAdventureCharacter::UseTool()
{
	if (SelectedTool)
	{
		UseItem(SelectedTool);
		OnUseTool(SelectedTool);
	}
}


void AAdventureCharacter::OnUseTool_Implementation(ATool* Tool)
{
	// can be overwitten by blueprint
}

void AAdventureCharacter::OnVehicleEnter()
{
	// Handle vehicle enter event, if needed
}

void AAdventureCharacter::OnVehicleExit()
{
	// Handle vehicle exit event, if needed
}

void AAdventureCharacter::StartVehicleHandBrake()
{
	if (CurrentVehicle)
	{
		CurrentVehicle->EngageHandbrake();
	}
}

void AAdventureCharacter::StopVehicleHandBrake()
{
	if (CurrentVehicle)
	{
		CurrentVehicle->ReleaseHandbrake();
	}
}


void AAdventureCharacter::StartVehicleHandNOS()
{
	if (CurrentVehicle)
	{
		CurrentVehicle->ActivateNOS();
	}
}

void AAdventureCharacter::StopVehicleHandNOS()
{
	if (CurrentVehicle)
	{
		CurrentVehicle->DeactivateNOS();
	}
}

void AAdventureCharacter::MenuAccept()
{
	if (CurrentInteractionActor) {
		CurrentInteractionActor->AcceptInteraction();
	}
	CloseInteraction();
	CloseMenu();
	CloseMap();
	CloseInventar();

}

void AAdventureCharacter::MenuDeny()
{
	if (CurrentInteractionActor)
	{
		CurrentInteractionActor->DenyInteraction();
	}
	CloseInteraction();
	CloseMenu();
	CloseMap();
	CloseInventar();
	if (GameMode && GameMode->IsPaused() && !GUIIsActive())
	{
		GameMode->ResumeGame();
	}

}

void AAdventureCharacter::MenuPrevTab()
{

}

void AAdventureCharacter::MenuNextTab()
{

}

void AAdventureCharacter::MenuPrevOption()
{

}

void AAdventureCharacter::MenuNextOption()
{

}

bool AAdventureCharacter::CanAttackCharacter(AAdventureCharacter* Character)
{
	if (Character)
	{
		
	}
	return false;
}
