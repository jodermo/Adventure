#include "AdventurePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AdventureCharacter.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AAdventurePlayerController::AAdventurePlayerController()
{
	Logger = CreateDefaultSubobject<ULogging>(TEXT("Logger"));
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AAdventurePlayerController::BeginPlay()
{
	Super::BeginPlay();


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	InitGame();
	if (GameMode) {
		GameMode->PlayerControllers.Add(this);
	}
}

void AAdventurePlayerController::InitGame()
{
	APawn* ControlledPawn = GetPawn();
	Character = Cast<AAdventureCharacter>(ControlledPawn);
	Player = Cast<APlayerCharacter>(ControlledPawn);
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
}

void AAdventurePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// bAutoManageActiveCameraTarget = false;


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{


		/** Game **/
		EnhancedInputComponent->BindAction(GameStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnGameStart);
		EnhancedInputComponent->BindAction(GamePauseAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnGamePause);
		EnhancedInputComponent->BindAction(GameResumeAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnGameResume);
		EnhancedInputComponent->BindAction(GamStopAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnGameStop);

		/** Menu **/
		EnhancedInputComponent->BindAction(MenuAcceptAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuAccept);
		EnhancedInputComponent->BindAction(MenuDenyAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuDeny);
		EnhancedInputComponent->BindAction(MenuPrevTabAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuPrevTab);
		EnhancedInputComponent->BindAction(MenuNextTabAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuNextTab);
		EnhancedInputComponent->BindAction(MenuPrevOptionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuPrevOption);
		EnhancedInputComponent->BindAction(MenuNextOptionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuNextOption);

		/** Menus / Interactions/ Inventars **/
		EnhancedInputComponent->BindAction(MenuOpenAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnMenuOpen);
		EnhancedInputComponent->BindAction(MenuCloseAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnMenuClose);
		EnhancedInputComponent->BindAction(InventarOpenAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnInventarOpen);
		EnhancedInputComponent->BindAction(InventarCloseAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnInventarClose);

		EnhancedInputComponent->BindAction(NewPlayerInteraction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnNewInteraction);
		EnhancedInputComponent->BindAction(JoinPlayerInteraction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnJoinInteraction);
		EnhancedInputComponent->BindAction(LeavePlayerInteraction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnLeaveInteraction);

		/** Camera **/

		EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnSwitchCamera);
		EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnZoomIn);
		EnhancedInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnZoomOut);


		/** Character **/

		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AAdventurePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AAdventurePlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnLookUp);
		EnhancedInputComponent->BindAction(LookRightAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnLookRight);
		EnhancedInputComponent->BindAction(MouseUpAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMouseUp);
		EnhancedInputComponent->BindAction(MouseRightAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMouseRight);

		EnhancedInputComponent->BindAction(MoveCameraUpAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMoveCameraUp);
		EnhancedInputComponent->BindAction(MoveCameraForwardAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMoveCameraForward);
		EnhancedInputComponent->BindAction(MoveCameraRightAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMoveCameraRight);

		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnMoveRight);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnJump);

		EnhancedInputComponent->BindAction(Interact, ETriggerEvent::Started, this, &AAdventurePlayerController::OnInteract);


		EnhancedInputComponent->BindAction(GrabActorAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnGrabActor);
		EnhancedInputComponent->BindAction(DropActorAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnDropActor);
		EnhancedInputComponent->BindAction(ThrowActorAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnThrowActor);


		EnhancedInputComponent->BindAction(PrimaryWeaponPrimaryActionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnPrimaryWeaponPrimaryAction);
		EnhancedInputComponent->BindAction(PrimaryWeaponSecondaryActionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnPrimaryWeaponSecondaryAction);
		EnhancedInputComponent->BindAction(SecondaryWeaponPrimaryActionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnSecondaryWeaponPrimaryAction);
		EnhancedInputComponent->BindAction(SecondaryWeaponSecondaryActionAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnSecondaryWeaponSecondaryAction);


		EnhancedInputComponent->BindAction(UseItemsAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnUseItems);
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnUserTool);


		EnhancedInputComponent->BindAction(SprintStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnSprintActionPressed);
		EnhancedInputComponent->BindAction(SprintStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnSprintActionReleased);

		EnhancedInputComponent->BindAction(SprintStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnSprintActionPressed);
		EnhancedInputComponent->BindAction(SprintStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnSprintActionReleased);

		EnhancedInputComponent->BindAction(CrouchStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnCrouchActionPressed);
		EnhancedInputComponent->BindAction(CrouchStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnCrouchActionReleased);

		EnhancedInputComponent->BindAction(ClimbStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnStartClimbing);
		EnhancedInputComponent->BindAction(ClimbStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnStopClimbing);

		/** Vehicle **/

		EnhancedInputComponent->BindAction(DriveForwardAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnDriveForward);
		EnhancedInputComponent->BindAction(DriveRightAction, ETriggerEvent::Triggered, this, &AAdventurePlayerController::OnDriveRight);

		EnhancedInputComponent->BindAction(HandbrakeStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnStartVehicleHandBrake);
		EnhancedInputComponent->BindAction(HandbrakeStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnStopVehicleHandBrake);

		EnhancedInputComponent->BindAction(NOSStartAction, ETriggerEvent::Started, this, &AAdventurePlayerController::OnStartVehicleHandBrake);
		EnhancedInputComponent->BindAction(NOSStopAction, ETriggerEvent::Completed, this, &AAdventurePlayerController::OnStopVehicleHandBrake);


	}
}

void AAdventurePlayerController::OnInputStarted()
{
	StopMovement();
}

APlayerCharacter* AAdventurePlayerController::GetCharacterForPlayerIndex(int PlayerIndex)
{
	if (Character && Character->GameMode)
	{
		if (Character->GameMode->MouseInteractionPlayer)
		{
			return Character->GameMode->MouseInteractionPlayer;
		}
		if (PlayerIndex < Character->GameMode->Players.Num())
		{
			return Character->GameMode->Players[PlayerIndex];
		}
	}
	return Player;
}

int AAdventurePlayerController::GetPlayerIndexFromDestination(int PlayerCount, FVector Destination)
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	int ClickedPlayerIndex = 0;
	if (PlayerCount == 1) {
		ClickedPlayerIndex = 0;
	}
	else if (PlayerCount == 2) {
		if (Destination.Y > ViewportSize.Y / 2) {
			ClickedPlayerIndex = 0;
		}
		else {
			ClickedPlayerIndex = 1;
		}
	}
	else if (PlayerCount == 3) {
		float ThirdOfHeight = ViewportSize.Y / 3;
		if (Destination.Y > ThirdOfHeight * 2) {
			ClickedPlayerIndex = 0;
		}
		else if (Destination.Y > ThirdOfHeight) {
			ClickedPlayerIndex = 1; 
		}
		else {
			ClickedPlayerIndex = 2;
		}
	}
	else if (PlayerCount == 4) {
		float HalfWidth = ViewportSize.X / 2;
		float HalfHeight = ViewportSize.Y / 2;
		if (Destination.Y > HalfHeight) {
			if (Destination.X > HalfWidth) {
				ClickedPlayerIndex = 0;
			}
			else {
				ClickedPlayerIndex = 1;
			}
		}
		else {
			if (Destination.X > HalfWidth) {
				ClickedPlayerIndex = 2;
			}
			else {
				ClickedPlayerIndex = 3;
			}
		}
	}
	return ClickedPlayerIndex;
}

void AAdventurePlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	APlayerCharacter* PlayerOfTheView = Player;
	if (Character && Character->GameMode)
	{
		int PlayerCount = Character->GameMode->Players.Num();
		int ClickedPlayerIndex = GetPlayerIndexFromDestination(PlayerCount, CachedDestination);
		PlayerOfTheView = GetCharacterForPlayerIndex(ClickedPlayerIndex);
	}
	if (Character == PlayerOfTheView && !Character->EgoView && !Character->ThirdPersonView && !Character->CurrentVehicle && Character->CanMove)
	{
		FVector WorldDirection = (CachedDestination - Character->GetActorLocation()).GetSafeNormal();
		Character->MoveDirection(WorldDirection, FollowTime);
	}
	else {
		FollowTime = 0.f;
	}
}

void AAdventurePlayerController::OnSetDestinationReleased()
{
	APlayerCharacter* PlayerOfTheView = Player;
	int ClickedPlayerIndex = 0;
	if (Character && Character->GameMode) 
	{
		int PlayerCount = Character->GameMode->Players.Num();
		ClickedPlayerIndex = GetPlayerIndexFromDestination(PlayerCount, CachedDestination);
		PlayerOfTheView = GetCharacterForPlayerIndex(ClickedPlayerIndex);
	}
	if (Character == PlayerOfTheView && !Character->EgoView && !Character->ThirdPersonView && !Character->CurrentVehicle)
	{
		if (FollowTime <= ShortPressThreshold && Character->CanMove)
		{
			// FVector Offset = PlayerOfTheView->GetActorLocation() - Character->GetActorLocation();
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Character->PlayerController, CachedDestination );
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(Character->PlayerController, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		FollowTime = 0.f;
	}
}

void AAdventurePlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AAdventurePlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AAdventurePlayerController::OnMenuAccept(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuAccept();
	}
}

void AAdventurePlayerController::OnMenuDeny(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuDeny();
	}
}

void AAdventurePlayerController::OnMenuPrevTab(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuPrevTab();
	}
}

void AAdventurePlayerController::OnMenuNextTab(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuNextTab();
	}
}
void AAdventurePlayerController::OnMenuPrevOption(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuPrevOption();
	}
}

void AAdventurePlayerController::OnMenuNextOption(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MenuNextOption();
	}
}

void AAdventurePlayerController::OnSwitchCamera(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->SwitchCamera();
	}
}

void AAdventurePlayerController::OnLookUp(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->LookUp(Value.Get<float>() * ControllerSensitivity);
	}
}

void AAdventurePlayerController::OnLookRight(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->LookRight(Value.Get<float>() * ControllerSensitivity);
	}
}


void AAdventurePlayerController::OnMouseUp(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->LookUp(Value.Get<float>() * MouseSensitivity);
	}
}

void AAdventurePlayerController::OnMouseRight(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->LookRight(Value.Get<float>() * MouseSensitivity);
	}
}


void AAdventurePlayerController::OnMoveForward(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MoveForward(Value.Get<float>());
	}
}


void AAdventurePlayerController::OnMoveRight(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MoveRight(Value.Get<float>());
	}
}

void AAdventurePlayerController::OnDriveForward(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->DriveForward(Value.Get<float>());
	}
}

void AAdventurePlayerController::OnDriveRight(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->DriveRight(Value.Get<float>());
	}
}
void AAdventurePlayerController::OnMoveCameraUp(const FInputActionValue& Value)
{
	if (Character)
	{
		// Character->MoveCameraUp(Value.Get<float>());
	}
}

void AAdventurePlayerController::OnMoveCameraForward(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MoveCameraForward(Value.Get<float>());
	}
}

void AAdventurePlayerController::OnMoveCameraRight(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->MoveCameraRight(Value.Get<float>());
	}
}


void AAdventurePlayerController::OnJump(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Jump();
	}
}

void AAdventurePlayerController::OnStartClimbing(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StartClimbing();
	}
}

void AAdventurePlayerController::OnStopClimbing(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StopClimbing();
	}
}

void AAdventurePlayerController::OnInteract(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Interact(nullptr);
	}
}


void AAdventurePlayerController::OnPrimaryWeaponPrimaryAction(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->PrimaryAction(false);
	}
}

void AAdventurePlayerController::OnPrimaryWeaponSecondaryAction(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->PrimaryAction(true);
	}
}

void AAdventurePlayerController::OnSecondaryWeaponPrimaryAction(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->SecondaryAction(false);
	}
}

void AAdventurePlayerController::OnSecondaryWeaponSecondaryAction(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->SecondaryAction(true);
	}
}




void AAdventurePlayerController::OnUseItems(const FInputActionValue& Value)
{

	if (Character)
	{
		Character->UseItems();
	}
}

void AAdventurePlayerController::OnUserTool(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->UseTool();
	}
}

void AAdventurePlayerController::OnStartVehicleHandBrake(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StartVehicleHandBrake();
	}
}

void AAdventurePlayerController::OnStopVehicleHandBrake(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StopVehicleHandBrake();
	}
}

void AAdventurePlayerController::OnStartVehicleNOS(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StartVehicleHandNOS();
	}
}

void AAdventurePlayerController::OnStopVehicleNOS(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->StopVehicleHandNOS();
	}
}


void AAdventurePlayerController::OnNewInteraction(const FInputActionValue& Value)
{
	if (Player)
	{
		Player->NewPlayerInteraction();
	}
}

void AAdventurePlayerController::OnJoinInteraction(const FInputActionValue& Value)
{
	if (Player && Player->SelectedPlayerInteraction)
	{
		Player->JoinPlayerInteraction(Player->SelectedPlayerInteraction);
	}
	else if (Player)
	{
		Player->ShowPlayerInteractionSelection();
	}
}

void AAdventurePlayerController::OnLeaveInteraction(const FInputActionValue& Value)
{
	if (Player)
	{
		Player->CancelPlayerInteraction();
	}
}

void AAdventurePlayerController::OnSprintActionPressed(const FInputActionValue& Value)
{
	if (Character && !Character->IsSprinting)
	{
		Character->StartSprint();
	}
}

void AAdventurePlayerController::OnSprintActionReleased(const FInputActionValue& Value)
{
	if (Character && Character->IsSprinting)
	{
		Character->StopSprint();
	}
}

void AAdventurePlayerController::OnCrouchActionPressed(const FInputActionValue& Value)
{
	if (Character && !Character->IsCrouching)
	{
		Character->StartCrouch();
	}
}

void AAdventurePlayerController::OnCrouchActionReleased(const FInputActionValue& Value)
{
	if (Character && Character->IsCrouching)
	{
		Character->StopCrouch();
	}
}

void AAdventurePlayerController::OnZoom(float ZoomValue)
{
	if (Character)
	{
		Character->ZoomCamera(ZoomValue);
	}
}

void AAdventurePlayerController::OnZoomIn(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->ZoomCamera(ZoomStepSize);
	}
}

void AAdventurePlayerController::OnZoomOut(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->ZoomCamera(-ZoomStepSize);
	}
}

void AAdventurePlayerController::OnMenuOpen(const FInputActionValue& Value)
{
	if (GameMode)
	{
		if (!GameMode->MenuVisible)
		{
			GameMode->ShownMenu();
		}
	}
}

void AAdventurePlayerController::OnMenuClose(const FInputActionValue& Value)
{
	if (GameMode)
	{
		if (GameMode->MenuVisible)
		{
			GameMode->CloseMenu();
		}
	}
}

void AAdventurePlayerController::OnInventarOpen(const FInputActionValue& Value)
{
	if (GameMode)
	{
		if (!GameMode->InventarVisible)
		{
			GameMode->ShowInventar();
		}
	}
}

void AAdventurePlayerController::OnInventarClose(const FInputActionValue& Value)
{
	if (GameMode)
	{
		if (GameMode->InventarVisible)
		{
			GameMode->CloseInventar();
		}
	}
}

void AAdventurePlayerController::OnGameStart(const FInputActionValue& Value)
{
	if (GameMode)
	{
		GameMode->StartGame();
	}
}

void AAdventurePlayerController::OnGamePause(const FInputActionValue& Value)
{
	if (GameMode)
	{
		GameMode->PauseGame();
	}
}

void AAdventurePlayerController::OnGameResume(const FInputActionValue& Value)
{
	if (GameMode)
	{
		GameMode->ResumeGame();
	}
}

void AAdventurePlayerController::OnGameStop(const FInputActionValue& Value)
{
	if (GameMode)
	{
		GameMode->StopGame();
	}
}



void AAdventurePlayerController::OnGrabActor(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->GrabClosestActor();
	}
}

void AAdventurePlayerController::OnDropActor(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->DropActor();
	}
}

void AAdventurePlayerController::OnThrowActor(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->ThrowActorForward();
	}
}
