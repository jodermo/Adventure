
#pragma once

#include "Logging/StructuredLog.h"
#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "ItemActor.h"
#include "Tool.h"
#include "Weapon.h"
#include "AreaActor.h"
#include "Vehicle.h"
#include "TaskArea.h"
#include "AdventurePlayerController.h"
#include "AdventureGameModeBase.h"
#include "CharacterInteractionComponent.h"
#include "CharacterLogging.h"
#include "InteractionActor.h"
#include "TaskActor.h"
#include "Engine/StaticMesh.h"
#include "RecastGameNavMesh.h"
#include "SpeechComponent.h"
#include "AdventureCharacterProperties.h"
#include "CharacterCameraController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "AdventureCharacter.generated.h"


UCLASS(Blueprintable)
class AAdventureCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	AAdventureCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ToolTip = "Main properties of the character"))
	UAdventureCharacterProperties* Properties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ToolTip = "Camera settings of the character"))
	UCharacterCameraController* CameraController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (ToolTip = "Interaction component of the character"))
	UCharacterInteractionComponent* InteractionComponent;

	virtual void UpdateAttributes();



	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Initiates an attack on the target character"))
	virtual void Attack(AAdventureCharacter* TargetCharacter, float DamageFactor, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Calculates the attack damage to be dealt to the target character"))
	virtual float GetAttackDamage(AAdventureCharacter* TargetCharacter, float DamageFactor, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Adds new points to the character's accumulated points"))
	virtual int AddPoints(int NewPoints);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Log a message related to the character"))
	void ShowSpeechBuuble(FString Text, float FontSize, float Duration);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the eye location"))
	FVector EyesLocation = FVector(25.0f, 0.0f, 80.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset of the eye trace, to prevent tracing own mesh"))
	FVector EyeTraceStartOffset = FVector(40.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Navigation Mesh"))
	ARecastGameNavMesh* NavigationMesh;



	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Camera component attached to the character"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Spring arm component for camera positioning"))
	class USpringArmComponent* CameraBoom;

	bool CameraBoomVehicleMode = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Camera component attached to the character"))
	class UCameraComponent* MapCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Spring arm component for map camera positioning"))
	class USpringArmComponent* MapCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Camera component attached to the character"))
	class UCameraComponent* CurrentCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Minimum camera distance from the character"))
	float TopDownCameraDistance = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the top-down camera"))
	FVector TopDownCameraOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the top-down camera"))
	FVector TopDownCameraPosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to rotate the top-down camera along with the player's movement"))
	bool CanMoveCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the top-down camera"))
	FVector MapCameraOffset = FVector(0.0f, 0.0f, 500.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the top-down camera"))
	FVector MapCameraPosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the top-down camera"))
	float TopDownMapCameraSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the third-person camera"))
	FVector ThirdPersonCameraOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Offset for the ego camera"))
	FVector EgoCameraOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Rotation angle for the top-down camera view"))
	float TopDownCameraRotationAngle = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Rotation angle for the top-down camera view"))
	float MapCameraRotationAngle = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Flag to rotate the top-down camera along with the player's movement"))
	bool RotateTopDownWithPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Rotation angle for the third-person camera view"))
	float ThirdPersonRotationAngle = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Minimum camera distance from the character"))
	float MinCameraDistance = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Default camera distance from the character"))
	float CameraDistance = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Top-down camera distance from the character"))
	float MapCameraDistance = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Third-person camera distance from the character"))
	float ThirdPersonCameraDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Maximum camera distance from the character"))
	float MaxCameraDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Speed at which the camera zooms"))
	float ZoomSpeed = 1000.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Speed at which the camera zooms"))
	float CameraBackToNormalSpeed = 1.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The static mesh component of the interaction actor"))
	UStaticMeshComponent* PrimaryCrosshairMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The static mesh component of the interaction actor"))
	UStaticMeshComponent* SecondaryCrosshairMesh;

	virtual void UpdateCrosshairMesh(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Reference to the pawn owned by the player"))
	APawn* PlayerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Reference to the character owned by the player"))
	AAdventureCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Reference to the character controller"))
	AAdventurePlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Reference to the character controller"))
	AAdventurePlayerController* CharacterController;

	virtual void InitCharacter() override;



	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Zoom the camera in or out based on input"))
	void ZoomCamera(float ZoomInput);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Update the camera's position based on the given delta time"))
	void UpdateCameraPosition(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Update the camera's rotation based on the given delta time"))
	void UpdateCameraRotation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Update the face capture camera's rotation based on the given delta time"))
	void UpdateFaceCapture(float DeltaTime);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The character's current attention level"))
	float Attention = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The character's level of conspicuousness"))
	float Conspicuousness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The character's concealment level"))
	float Concealment = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The distance at which other characters can recognize this character"))
	float RecognitionDistance = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "An array of characters that are currently being followed by this character"))
	TArray<AAdventureCharacter*> FollowingCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "List of characters to ignore"))
	TArray<AAdventureCharacter*> IgnoreCharacters;


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Adds character to IgnoreCharacters list"))
	virtual void IgnoreCharacter(AAdventureCharacter* CharacterToIgnore);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "removes character from IgnoreCharacters list"))
	virtual void UnignoreCharacter(AAdventureCharacter* CharacterToIgnore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The speed of the character when sprinting"))
	float SprintSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The walking speed of the character"))
	float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The speed of the character when crouching"))
	float CrouchSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The speed of the character when crouching and sprinting"))
	float CrouchSprintSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The reduction in recognition distance when crouching"))
	float ReduceRecognitionDistanceCrouching = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The increase in recognition distance when sprinting"))
	float AddRecognitionDistanceSprinting = 100.0f;




	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Move the character in a given direction with a specified amount"))
	virtual void MoveDirection(FVector DirectionVector, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Rotate the character to face a specific direction"))
	virtual void LookDirection(FVector DirectionVector);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop the character's movement"))
	virtual void StopMoving();


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start crouching the character"))
	virtual void StartCrouch();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop crouching the character"))
	virtual void StopCrouch();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start sprinting the character"))
	virtual void StartSprint();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop sprinting the character"))
	virtual void StopSprint();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Toggle the character's sprinting state"))
	virtual void ToggleSprinting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "HideMeshInEgoView"))
	bool HideMeshInEgoView = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The number of times the character can jump before landing"))
	int32 CanJumpForCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Allows the character to perform a double jump"))
	bool CanDoubleJump = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The number of times the character has jumped"))
	int32 JumpCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The current movement speed of the character"))
	float JumpHeight = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The current movement speed of the character"))
	float JumpGravity = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The Scene Capture Component used for face capture", AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* FaceCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The Spring Arm Component used for face capture", AllowPrivateAccess = "true"))
	class USpringArmComponent* FaceCaptureSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "FaceCapturePosition"))
	FVector FaceCapturePosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "FaceCaptureRotation"))
	FRotator FaceCaptureRotation = FRotator(0.0f, 180.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "CaptureFace"))
	bool DoCaptureFace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The distance of the minimap camera from the character"))
	float FaceCaptureDistance = 60.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The Scene Capture Component used for the minimap", AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* MiniMapSceneCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "The Spring Arm Component used for the minimap", AllowPrivateAccess = "true"))
	class USpringArmComponent* MiniMapSpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The distance of the minimap camera from the character"))
	float MiniMapCameraDistance = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The orthographic width of the minimap camera's view"))
	float MiniMapCameraOrthoWidth = 1000.0f;

	virtual void Jump() override;

	bool CanJumpInternal();

	virtual void Landed(const FHitResult& Hit) override;

	void ResetJumpCount();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Perform a character interaction from the target character."))
	virtual void TriggerInteractionActor(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Initiate interaction with another character"))
	virtual void DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Called when interaction with another character is triggered"))
	virtual void OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Called when the character interacts with an InteractionActor"))
	virtual void OnCharacterActorInteraction(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Called when the character's collision overlaps with an area"))
	virtual void OnAreaOverlapBegin(AAreaActor* AreaActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Called when the character's collision ends overlapping with an area"))
	virtual void OnAreaOverlapEnd(AAreaActor* AreaActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Enable/disable the character's ability to pick up items"))
	bool PuckUpItems = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of collected items"))
	TArray<AItemActor*> CollectedItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of selected items"))
	TArray<AItemActor*> SelectedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Class of the next interaction actor triggered by selecting this answer."))
	TArray<TSubclassOf<AInteractionActor>> ItemInteractionActorClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of tools"))
	TArray<ATool*> Tools;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of weapons"))
	ATool* SelectedTool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of weapons"))
	TArray<AWeapon*> Weapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of weapons"))
	AWeapon* PrimaryWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of weapons"))
	AWeapon* SecondaryWeapon;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Check if an item is collected"))
	bool IsItemCollected(AItemActor* Item);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Pick up an item"))
	void PickupItem(AItemActor* Item, FName SlotName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnPickupItem(AItemActor* Item, FName SlotName);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Add item"))
	void AddItem(AItemActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnAddItem(AItemActor* Item);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Use an item"))
	void UseItem(AItemActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnUseItem(AItemActor* Item);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select an item"))
	void SelectItem(AItemActor* Item);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Unselect an item"))
	void UnselectItem(AItemActor* Item);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Check if an item is selected"))
	bool IsItemSelected(AItemActor* Item);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Toggle selection of an item"))
	void ToggleSelectItem(AItemActor* Item);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select an item"))
	void SelectTool(ATool* Tool);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select an item"))
	void SelectPrimaryWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select an item"))
	void SelectSecondaryWeapon(AWeapon* Weapon);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Check if Character GUI is active"))
	bool GUIIsActive();


	void UpdateGameInputState(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Set the game input mode, optionally showing the mouse cursor"))
	void SetGameInputMode(bool ShowMouseCursor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Switch between different camera views"))
	void SwitchCamera();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Set the camera to top-down view"))
	void SetTopDownView();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Set the camera to third-person view"))
	void SetThirdPersonView();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Set the camera to ego view"))
	void SetEgoView();

	FString LastCameraMode = FString(TEXT("None"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The static mesh component of the interaction actor"))
	UStaticMeshComponent* InteractionActorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of collected interaction actors"))
	TArray<AInteractionActor*> CollectedInteractionActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The currently interacting interaction actor"))
	AInteractionActor* CurrentInteractionActor;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Add an interaction actor to the collected list"))
	void AddInteractionActor(AInteractionActor* InteractionActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Remove an interaction actor from the collected list"))
	void RemoveInteractionActor(AInteractionActor* InteractionActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select an interaction actor for interaction"))
	void SelectInteractionActor(AInteractionActor* InteractionActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The static mesh component of the task actor"))
	UStaticMeshComponent* TaskActorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "List of collected task actors"))
	TArray<ATaskActor*> CollectedTaskActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The currently selected task actor"))
	ATaskActor* CurrentTaskActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Areas known to character"))
	TArray<AAreaActor*> TargetAreas;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Add a task actor to the collected list"))
	void AddTaskActor(ATaskActor* TaskActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Add a task actor to the collected list"))
	void AddTargetArea(ATaskActor* TaskActor, AAreaActor* AreaActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Remove a task actor from the collected list"))
	void RemoveTaskActor(ATaskActor* TaskActor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Select a task actor for interaction"))
	void SelectTaskActor(ATaskActor* TaskActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The distance to objects for climbing"))
	float ClimbCheckDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The speed for climbing"))
	float ClimbingSpeed = 10.0f;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuAccept"))
	virtual bool CharacterCanMove();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuAccept"))
	virtual bool CharacterCanAttack();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuAccept"))
	virtual bool CharacterCanInteract();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start climb on object"))
	void StartClimbing();


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop climb on object"))
	void StopClimbing();

	void CheckNearClimbable();
	void UpdateClimbing(float DeltaTime);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuAccept"))
	virtual void MenuAccept();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuDeny"))
	virtual void MenuDeny();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuPrevTab"))
	virtual void MenuPrevTab();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuNextTab"))
	virtual void MenuNextTab();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuPrevOption"))
	virtual void MenuPrevOption();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuNextOption"))
	virtual void MenuNextOption();


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "TurnUp"))
	void LookUp(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "TurnRight"))
	void LookRight(float Value);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveForward"))
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveForward"))
	void DriveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveRight"))
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveRight"))
	void DriveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveCameraUp"))
	void MoveCameraUp(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveCameraForward"))
	void MoveCameraForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MoveCameraRight"))
	void MoveCameraRight(float Value);

	void SetMapView();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Whether the inventory is visible."))
	bool MenuVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Whether the inventory is visible."))
	bool InventarVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "Whether the controls are visible."))
	bool ControlsVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the controls are visible."))
	bool MapVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the controls are visible."))
	bool InteractionVisible = false;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Show the menu."))
	void ShowMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Close the menu."))
	void CloseMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Show the inventory."))
	void ShowInventar();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Close the inventory."))
	void CloseInventar();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Show the controls."))
	void ShowControls();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Close the controls."))
	void CloseControls();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Show the map."))
	void ShowMap();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Close the map."))
	void CloseMap();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Show the map."))
	void ShowInteraction();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Close the map."))
	void CloseInteraction();

	UPROPERTY(EditAnywhere, Category = "Game Character")
	float DampeningFactor = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Game Character")
	float RollingDampeningFactor = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Character")
	float AdditionalForceFactor = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Game Character")
	float FixedDampeningForceMagnitude = 1000.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MaxVehicleDistance"))
	float MaxVehicleDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "VehicleImpactMultiplier"))
	float VehicleImpactMultiplier =.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MinVehicleImpactForce"))
	float MinVehicleImpactForce = 1.0f;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Character", meta = (ToolTip = "Current vehicle"))
	AVehicle* CurrentVehicle;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "EnterVehicle."))
	void EnterVehicle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnEnterVehicle(AVehicle* Vehicle);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "ExitVehicle."))
	void ExitVehicle();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnExitVehicle(AVehicle* Vehicle);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void Interact(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnInteract(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void PrimaryAction(bool SecondaryActionMode);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnPrimaryAction(AWeapon* Weapon, bool SecondaryActionMode);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void SecondaryAction(bool SecondaryActionMode);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnSecondaryAction(AWeapon* Weapon, bool SecondaryActionMode);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void UseItems();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnUseItems(const TArray<AItemActor*>& Items);


	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Interact."))
	void UseTool();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnUseTool(ATool* Tool);



	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start climb on object"))
	void StartVehicleHandBrake();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop climb on object"))
	void StopVehicleHandBrake();



	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start climb on object"))
	void StartVehicleHandNOS();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Stop climb on object"))
	void StopVehicleHandNOS();



	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Check if a character is available for an attack"))
	virtual bool CanAttackCharacter(AAdventureCharacter* Character);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Components", meta = (ToolTip = "ItemPickUpSpeechComponent"))
	USpeechComponent* ItemPickUpSpeechComponent;


	void OnVehicleEnter();
	void OnVehicleExit();
	virtual AVehicle* GetClosestVehicle();

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "Start climb on object"))
	void PauseGame();

protected:

	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


	void BeginPlay() override;

private:
	FTimerHandle TimerHandle_RevertPhysics;
	FTimerHandle TimerHandle_DelayedPause;


};

