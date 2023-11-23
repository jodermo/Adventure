#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputCoreTypes.h"
#include "Components/InputComponent.h" 
#include "Templates/SubclassOf.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "AdventureGameModeBase.h"
#include "Logging.h"
#include "Engine/GameInstance.h"
#include "AdventurePlayerController.generated.h"


class UNiagaraSystem;
class AAdventureCharacter;
class APlayerCharacter;

UCLASS()
class AAdventurePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAdventurePlayerController();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "Reference to the logging component for this player controller."))
	ULogging* Logger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (ToolTip = "Threshold value for a short press input event."))
	float ShortPressThreshold = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (ToolTip = "Particle system to display at the cursor location."))
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Default input mapping context for this player controller."))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for triggering destination on mouse click."))
	class UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for triggering destination on touch input."))
	class UInputAction* SetDestinationTouchAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for look up"))
	class UInputAction* LookUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for look right"))
	class UInputAction* LookRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for look up"))
	class UInputAction* MouseUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for look right"))
	class UInputAction* MouseRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for look right"))
	class UInputAction* MoveCameraUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for moving forward"))
	class UInputAction* MoveCameraForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for moving forward"))
	class UInputAction* MoveCameraRightAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for moving forward"))
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for moving right"))
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* ClimbStartAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* ClimbStopAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for primary action."))
	class UInputAction* PrimaryWeaponPrimaryActionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for primary action."))
	class UInputAction* PrimaryWeaponSecondaryActionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for primary action."))
	class UInputAction* SecondaryWeaponPrimaryActionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for secondary action."))
	class UInputAction* SecondaryWeaponSecondaryActionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for using item."))
	class UInputAction* UseItemsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for using tool."))
	class UInputAction* UseToolAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* SprintStartAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for stopping sprinting."))
	class UInputAction* SprintStopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting crouching."))
	class UInputAction* CrouchStartAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for stopping crouching."))
	class UInputAction* CrouchStopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for zooming in."))
	class UInputAction* SwitchCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for zooming in."))
	class UInputAction* ZoomInAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for zooming out."))
	class UInputAction* ZoomOutAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for zooming."))
	class UInputAction* ZoomAction;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for accept button in menu."))
	class UInputAction* MenuAcceptAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for deny button in menu."))
	class UInputAction* MenuDenyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for prev tab in menu."))
	class UInputAction* MenuPrevTabAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for next tab in menu."))
	class UInputAction* MenuNextTabAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for prev option in menu."))
	class UInputAction* MenuPrevOptionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for next option in menu."))
	class UInputAction* MenuNextOptionAction;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for opening the menu."))
	class UInputAction* MenuOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for closing the menu."))
	class UInputAction* MenuCloseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for opening the inventory."))
	class UInputAction* InventarOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for closing the inventory."))
	class UInputAction* InventarCloseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting the game."))
	class UInputAction* GameStartAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for pausing the game."))
	class UInputAction* GamePauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for resuming the game."))
	class UInputAction* GameResumeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for stopping the game."))
	class UInputAction* GamStopAction;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Create new Player to Player interaction."))
	class UInputAction* NewPlayerInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Join near Player to Player interactions."))
	class UInputAction* JoinPlayerInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input", meta = (AllowPrivateAccess = "true", ToolTip = "Leave current Player to Player interaction."))
	class UInputAction* LeavePlayerInteraction;





	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for driving forward"))
	class UInputAction* DriveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for driving right"))
	class UInputAction* DriveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* HandbrakeStartAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting sprinting."))
	class UInputAction* HandbrakeStopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting NOS."))
	class UInputAction* NOSStartAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle Input", meta = (AllowPrivateAccess = "true", ToolTip = "Input action for starting NOS."))
	class UInputAction* NOSStopAction;





	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Movement", meta = (ToolTip = "Duration for the crouch action."))
	float CrouchDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Camera", meta = (ToolTip = "Step size for zooming in and out."))
	float ZoomStepSize = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controller", meta = (ToolTip = "CachedDestination"))
	FVector CachedDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Mouse", meta = (ToolTip = "MouseSensitivity"))
	float ControllerSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Mouse", meta = (ToolTip = "MouseSensitivity"))
	float MouseSensitivity = 0.05f;

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	APlayerCharacter* GetCharacterForPlayerIndex(int PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	int GetPlayerIndexFromDestination(int PlayerCount, FVector Destination);

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void OnSetDestinationTriggered();

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void OnSetDestinationReleased();

	AAdventureCharacter* Character;
	APlayerCharacter* Player;
	AAdventureGameModeBase* GameMode;


public:
	void InitGame();
	void OnInputStarted();
	void OnTouchTriggered();
	void OnTouchReleased();
	void OnSprintActionPressed(const FInputActionValue& Value);
	void OnSprintActionReleased(const FInputActionValue& Value);
	void OnCrouchActionPressed(const FInputActionValue& Value);
	void OnCrouchActionReleased(const FInputActionValue& Value);
	void OnLookUp(const FInputActionValue& Value);
	void OnLookRight(const FInputActionValue& Value);
	void OnMouseUp(const FInputActionValue& Value);
	void OnMouseRight(const FInputActionValue& Value);
	void OnZoom(float ZoomValue);
	void OnZoomIn(const FInputActionValue& Value);
	void OnZoomOut(const FInputActionValue& Value);
	void OnMenuOpen(const FInputActionValue& Value);
	void OnMenuClose(const FInputActionValue& Value);
	void OnInventarOpen(const FInputActionValue& Value);
	void OnInventarClose(const FInputActionValue& Value);
	void OnGameStart(const FInputActionValue& Value);
	void OnGamePause(const FInputActionValue& Value);
	void OnGameResume(const FInputActionValue& Value);
	void OnGameStop(const FInputActionValue& Value);
	void OnSwitchCamera(const FInputActionValue& Value);
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);

	void OnMoveCameraUp(const FInputActionValue& Value);
	void OnMoveCameraForward(const FInputActionValue& Value);
	void OnMoveCameraRight(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnStartClimbing(const FInputActionValue& Value);
	void OnStopClimbing(const FInputActionValue& Value);
	void OnInteract(const FInputActionValue& Value);

	void OnPrimaryWeaponPrimaryAction(const FInputActionValue& Value);
	void OnPrimaryWeaponSecondaryAction(const FInputActionValue& Value);
	void OnSecondaryWeaponPrimaryAction(const FInputActionValue& Value);
	void OnSecondaryWeaponSecondaryAction(const FInputActionValue& Value);
	void OnUseItems(const FInputActionValue& Value);
	void OnUserTool(const FInputActionValue& Value);

	void OnNewInteraction(const FInputActionValue& Value);
	void OnJoinInteraction(const FInputActionValue& Value);
	void OnLeaveInteraction(const FInputActionValue& Value);
	void OnMenuAccept(const FInputActionValue& Value);
	void OnMenuDeny(const FInputActionValue& Value);
	void OnMenuPrevTab(const FInputActionValue& Value);
	void OnMenuNextTab(const FInputActionValue& Value);
	void OnMenuPrevOption(const FInputActionValue& Value);
	void OnMenuNextOption(const FInputActionValue& Value);

	void OnDriveForward(const FInputActionValue& Value);
	void OnDriveRight(const FInputActionValue& Value);
	void OnStartVehicleHandBrake(const FInputActionValue& Value);
	void OnStopVehicleHandBrake(const FInputActionValue& Value);
	void OnStartVehicleNOS(const FInputActionValue& Value);
	void OnStopVehicleNOS(const FInputActionValue& Value);

protected:

	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

private:

	bool bIsTouch;
	float FollowTime;
};



