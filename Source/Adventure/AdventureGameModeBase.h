
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameLogging.h"
#include "InteractionActor.h"
#include "TaskActor.h"
#include "Engine/EngineTypes.h"
#include "SpeechBubble.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Level.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LevelActorContainer.h"
#include "AdventureGameModeBase.generated.h"



class AAdventureCharacter;
class APlayerCharacter;
class AAdventurePlayerController;
class AVehicle;
class AEnvironmentalObject;
class ADraggableActor;

USTRUCT(BlueprintType)
struct FPlayerView
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (ToolTip = "Player View Size"))
	FVector2D Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (ToolTip = "Player View Position"))
	FVector2D Position;

};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ToolTip = "Player Controller"))
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ToolTip = "Player Character"))
	ULocalPlayer* Player;
};

UENUM(BlueprintType)
enum class EUnitConfiguration : uint8
{
	MPH UMETA(DisplayName = "mph"),
	KMH UMETA(DisplayName = "km/h")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartGameDelegate);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartGameDelegate, int32, GameScore);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartGameDelegate, int32, GameScore, FString, PlayerName);

UCLASS(minimalapi)
class AAdventureGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAdventureGameModeBase();

	TMap<ULocalPlayer*, APlayerCharacter*> LocalPlayerCharacterMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "The logger instance used for game logging."))
	UGameLogging* Logger;

	// Game Logging
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Key for character logging"))
	int32 LogKey = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Color for character logging messages"))
	FColor LogColor = FColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Time duration for which character logging messages will be displayed"))
	float LogTime = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Log a message related to the character"))
	void Log(FString LogMessage);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Levels"))
	TArray<FSoftObjectPath> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "StartingMapIndex"))
	int32 StartingMLevelIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "ChangeMap"))
	void OpenLevelByIndex(int32 LevelIndex);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "ChangeMap"))
	void OpenLevel(FName LevelName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "StartingMapIndex"))
	FName CurrentLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "PlayerCharacterClasses"))
	TArray<TSubclassOf<APlayerCharacter>> PlayerCharacterClasses;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	EUnitConfiguration UnitConfiguration = EUnitConfiguration::MPH;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Time duration for which character logging messages will be displayed"))
	float DelayReadyTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the game has started or not."))
	bool Ready = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the game has started or not."))
	bool Started = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Whether the game is over or not."))
	bool GameIsOver = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the in-game menu is visible."))
	bool MenuVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the inventory is visible."))
	bool InventarVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the controls are visible."))
	bool ControlsVisible = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of player controllers in the game."))
	TArray<AAdventurePlayerController*> PlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of player characters in the game."))
	TArray<APlayerCharacter*> Players;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters in the game."))
	TArray<AAdventureCharacter*> Characters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters has won."))
	TArray<AGameCharacter*> WinnerCharacters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters has lost."))
	TArray<AGameCharacter*> LooserCharacters;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters has won."))
	TArray<AGameCharacter*> InGameCharacters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters has lost."))
	TArray<AGameCharacter*> GameOverCharacters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down characters in the game."))
	TArray<ADraggableActor*> DraggableActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of vehicles in the game."))
	TArray<AVehicle*> Vehicles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down environmental object in the game."))
	TArray<AEnvironmentalObject*> EnvironmentalObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Array of spawn locations for players."))
	TArray<FVector> PlayerSpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Current Mouse Player"))
	APlayerCharacter* MouseInteractionPlayer;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Get Player View Infos"))
	FPlayerView GetPlayerView(int PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Adds a new player"))
	FPlayerInfo AddPlayer(TSubclassOf<APlayerCharacter> PlayerCharacterClass, UInputMappingContext* MappingContext);
	
	AAdventurePlayerController* CreateNewPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "SetupPlayerInput"))
	void SetupPlayerInput(AAdventurePlayerController* Controller, UInputMappingContext* InputMapping, ULocalPlayer* NewLocalPlayer);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "ChangePlayerClass"))
	void ChangePlayerClass(APlayerCharacter* PlayerCharacter, TSubclassOf<APlayerCharacter> PlayerCharacterClass);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "NextPlayerClass"))
	void SetNextPlayerClass(APlayerCharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "PreviousPlayerClass"))
	void SetPreviousPlayerClass(APlayerCharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Adds a new player"))
	TArray<TSubclassOf<APlayerCharacter>> GetAvailablePlayerClasses(APlayerCharacter* PlayerCharacter);


	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Adds a new player"))
	void RemoveLastPlayer();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Pause the game."))
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Resume the game."))
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Stop the game."))
	void StopGame();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "End the game and trigger the game over condition."))
	void GameOver(AGameCharacter* LooserCharacter, bool GameEnded);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "End the game and trigger the game over condition."))
	void WinGame(AGameCharacter* WinnerCharacter, bool GameEnded);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Restart the game."))
	void StartGame();


	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Restart the game."))
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Restart the current level."))
	void RestartLevel();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show the in-game menu."))
	void ShownMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Close the in-game menu."))
	void CloseMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show the inventory."))
	void ShowInventar();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Close the inventory."))
	void CloseInventar();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show the controls."))
	void ShowControls();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Close the controls."))
	void CloseControls();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "The currently interacting actor."))
	AInteractionActor* CurrentInteractionActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether an interaction is currently visible."))
	bool InteractionVisible = false;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show an interaction dialog."))
	void ShowInteraction(AInteractionActor* InteractionActor);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Hide the interaction dialog."))
	void CloseInteraction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "The currently active task actor."))
	ATaskActor* CurrentTaskActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether a task is currently visible."))
	bool TaskVisible = false;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show a task dialog."))
	void ShowTask(ATaskActor* TaskActor);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Hide the task dialog."))
	void HideTask();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Enable or disable toon shading."))
	bool ToonShading = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Color used for outlining elements."))
	FColor OutlineColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Color used for shadows."))
	FColor ShadowColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Color used for lighting."))
	FColor LightColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color."))
	FColor BackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Secondary background color."))
	FColor SecondaryBackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color."))
	FColor TextColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Secondary text color."))
	FColor SecondaryTextColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color for highlighted elements."))
	FColor HighlightBackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color for highlighted elements."))
	FColor HighlightTextColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color for disabled elements."))
	FColor DisabledBackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color for disabled elements."))
	FColor DisabledTextColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color of buttons."))
	FColor ButtonBackgroundColor = FColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color of buttons."))
	FColor ButtonTextColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color of buttons on hover."))
	FColor ButtonBackgroundColorHover = FColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color of buttons on hover."))
	FColor ButtonTextColorHover = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color of active buttons."))
	FColor ButtonBackgroundColorActive = FColor::Emerald;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color of active buttons."))
	FColor ButtonTextColorActive = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Background color of disabled buttons."))
	FColor ButtonBackgroundColorDisabled = FColor::Transparent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Text color of disabled buttons."))
	FColor ButtonTextColorDisabled = FColor::Silver;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (AllowPrivateAccess = "true", ToolTip = "The Scene Capture Component used for the mini-map."))
	class USceneCaptureComponent2D* MapSceneCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (AllowPrivateAccess = "true", ToolTip = "The Spring Arm Component for the mini-map camera."))
	class USpringArmComponent* MapSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Distance of the mini-map camera from the map."))
	float MapCameraDistance = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Orthographic width of the mini-map camera."))
	float MapCameraOrthoWidth = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "Whether the mini-map is currently visible."))
	bool MapVisible = false;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Show the mini-map."))
	void ShowMap();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Hide the mini-map."))
	void HideMap();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of post-process volumes in the game world."))
	TArray<APostProcessVolume*> PostProcessVolumes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of post-process materials in the game world."))
	TArray<UMaterialInterface*> PostProcessMaterials;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Retrieve and store post-process volumes and materials in the game world."))
	void GetPostProcessVolumes();

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Hide the task dialog."))
	void AttachMapCamera(USpringArmComponent* MapCameraBoom);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode", meta = (ToolTip = "DefaultSpeechBubbleClass"))
	TSubclassOf<ASpeechBubble> DefaultSpeechBubbleClass;

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "AddNewSpeechBubble."))
	virtual ASpeechBubble* CreateSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector Location, FRotator Rotation, FVector Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble> SpeechBubbleClass);

	virtual ASpeechBubble* AddSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector* Location, FRotator* Rotation, FVector* Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble>* SpeechBubbleClass);

	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "ActorIsChracter"))
	AAdventureCharacter* ActorIsChracter(AActor* Actor);

	UPROPERTY(BlueprintAssignable, Category = "Game Mode")
	FStartGameDelegate OnStartGame;


protected:
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void GameReady();
private:
	FTimerHandle TimerHandle_DelayedLoading;
};



