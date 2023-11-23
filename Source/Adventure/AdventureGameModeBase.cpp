

#include "AdventureGameModeBase.h"
#include "AdventurePlayerController.h"
#include "AdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraTypes.h"
#include "EngineUtils.h" 
#include "Engine/World.h"
#include "PlayerCharacter.h"


AAdventureGameModeBase::AAdventureGameModeBase()
{

	LocalPlayerCharacterMap = TMap<ULocalPlayer*, APlayerCharacter*>();
	PlayerControllerClass = AAdventurePlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Adventure/Blueprints/Characters/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Adventure/Blueprints/Controllers/BP_AdventurePlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	Logger = CreateDefaultSubobject<UGameLogging>(TEXT("Logger"));

	MapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MapSpringArm"));
	MapSpringArm->SetupAttachment(RootComponent);
	MapSpringArm->SetUsingAbsoluteRotation(true);
	MapSpringArm->TargetArmLength = MapCameraDistance;
	MapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.f, 0.f));
	MapSpringArm->bDoCollisionTest = false;
	MapSceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MapSceneCaptureComponent"));
	MapSceneCaptureComponent->SetupAttachment(MapSpringArm, USpringArmComponent::SocketName);
	// Set the capture component's properties for orthographic projection
	MapSceneCaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	MapSceneCaptureComponent->OrthoWidth = MapCameraOrthoWidth;


	// Set the starting map index
	if (StartingMLevelIndex >= 0 && StartingMLevelIndex < Levels.Num())
	{
		// Load the selected map class
		// DefaultPawnClass = Levels[StartingMLevelIndex];
	}
	else
	{
		// Handle an invalid map index (e.g., show an error message)
	}

}
void AAdventureGameModeBase::Log(FString LogMessage) {
	GEngine->AddOnScreenDebugMessage(LogKey, LogTime, LogColor, LogMessage);
}

void AAdventureGameModeBase::OpenLevelByIndex(int32 LevelIndex)
{
	if (LevelIndex >= 0 && LevelIndex < Levels.Num())
	{
		CurrentLevelName = *Levels[LevelIndex].GetAssetName();
		UGameplayStatics::OpenLevel(this, CurrentLevelName);
	}
}

void AAdventureGameModeBase::OpenLevel(FName LevelName)
{
	if (!CurrentLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, CurrentLevelName, false);
	}
	WinnerCharacters.Empty();
	LooserCharacters.Empty();

	UGameplayStatics::OpenLevel(this, CurrentLevelName);
	CurrentLevelName = LevelName;
}

void AAdventureGameModeBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AAdventureGameModeBase::BeginPlay()
{

	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		if (CurrentLevelName.IsNone())
		{
			FString MapName = World->GetMapName();
			if (MapName.StartsWith(TEXT("UEDPIE")))
			{
				int32 UnderscoreIdx;
				if (MapName.FindChar('_', UnderscoreIdx))
				{
					MapName = MapName.Mid(UnderscoreIdx + 1);
					if (MapName.FindChar('_', UnderscoreIdx))
					{
						MapName = MapName.Mid(UnderscoreIdx + 1);
					}
				}
			}
			CurrentLevelName = *MapName;
		}
	}
	GetPostProcessVolumes();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayedLoading, this, &AAdventureGameModeBase::GameReady, DelayReadyTime, false);
}

void AAdventureGameModeBase::GameReady()
{
	Ready = true;
}

void AAdventureGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAdventureGameModeBase::GetPostProcessVolumes()
{
	int32 Count = GetWorld()->PostProcessVolumes.Num();
	PostProcessVolumes.Empty();
	for (int32 Index = 0; Index < Count; ++Index)
	{
		APostProcessVolume* Volume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[Index]);
		if (Volume)
		{
			PostProcessVolumes.Add(Volume);
			FPostProcessSettings Settings = Volume->Settings;
			if (Settings.WeightedBlendables.Array.IsValidIndex(0))
			{
				UMaterialInterface* PostProcessMaterial = Cast<UMaterialInterface>(Settings.WeightedBlendables.Array[0].Object);
				if (PostProcessMaterial)
				{
					PostProcessMaterials.Add(PostProcessMaterial);
				}
			}
		}
	}
}

FPlayerView AAdventureGameModeBase::GetPlayerView(int PlayerIndex)
{
	FPlayerView Result;
	int PlayerCount = PlayerControllers.Num();
	FVector2D Size = FVector2D(1920.0f, 1080.0f);
	FVector2D Position = FVector2D(0.0f, 0.0f);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Size);
	}

	if (PlayerCount < 2) {
		// 1 Player
		Result.Size = Size;
		Result.Position = Position;
	}
	else if (PlayerCount < 3) {
		// 2 Players
		Result.Size = FVector2D(Size.X / 2, Size.Y);
		Result.Position = FVector2D(PlayerIndex * Result.Size.X, 0.0f);
	}
	else if (PlayerCount < 4) {
		// 3 Players
		if (PlayerIndex < 2) {
			// Top two players
			Result.Size = FVector2D(Size.X / 2, Size.Y / 2);
			Result.Position = FVector2D(PlayerIndex * Result.Size.X, 0.0f);
		}
		else {
			// Bottom full-width player
			Result.Size = FVector2D(Size.X, Size.Y / 2);
			Result.Position = FVector2D(0.0f, Size.Y / 2);
		}
	}
	else {
		// 4 Players
		Result.Size = FVector2D(Size.X / 2, Size.Y / 2);
		Result.Position = FVector2D((PlayerIndex % 2) * Result.Size.X, (PlayerIndex / 2) * Result.Size.Y);
	}

	return Result;
}


FPlayerInfo AAdventureGameModeBase::AddPlayer(TSubclassOf<APlayerCharacter> PlayerCharacterClass, UInputMappingContext* MappingContext)
{
	int PlayerIndex = Players.Num();
	FString OutError;
	FPlayerInfo Result;
	UGameInstance* GameInstance = GetGameInstance();
	APlayerController* Controller = nullptr;
	if (GameInstance)
	{
		ULocalPlayer* NewLocalPlayer = GameInstance->CreateLocalPlayer(PlayerIndex, OutError, true);
		APlayerController* PlayerController = NewLocalPlayer->GetPlayerController(GameInstance->GetWorld());
		AAdventurePlayerController* AdventurePlayerController = Cast<AAdventurePlayerController>(PlayerController);
		if (IsValid(AdventurePlayerController))
		{
			SetupPlayerInput(AdventurePlayerController, MappingContext, NewLocalPlayer);
		}
		Result.Player = NewLocalPlayer;
		Result.PlayerController = PlayerController;
	
	}
	return Result;
}

void AAdventureGameModeBase::SetupPlayerInput(AAdventurePlayerController* Controller, UInputMappingContext* InputMapping, ULocalPlayer* NewLocalPlayer)
{
	APlayerCharacter* PlayerCharacter = nullptr;
	if (Players.Num())
	{
		PlayerCharacter = Players[Players.Num() - 1];
	}
	if (PlayerCharacter) {
		Controller->Possess(PlayerCharacter);
		Controller->Player = PlayerCharacter;
		Controller->Character = PlayerCharacter;
		PlayerCharacter->LocalPlayer = NewLocalPlayer;
		PlayerCharacter->PlayerController = Controller;

	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = NewLocalPlayer ? NewLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() : nullptr;
	if (IsValid(Subsystem))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 1);
	}
}

AAdventurePlayerController* AAdventureGameModeBase::CreateNewPlayerController()
{
	if (!GetWorld()) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AAdventurePlayerController* NewController = GetWorld()->SpawnActor<AAdventurePlayerController>(AAdventurePlayerController::StaticClass(), SpawnParams);
	return NewController;
}


TArray<TSubclassOf<APlayerCharacter>> AAdventureGameModeBase::GetAvailablePlayerClasses(APlayerCharacter* PlayerCharacter)
{
	TArray<TSubclassOf<APlayerCharacter>> AvailablePlayerClasses;
	UClass* CurrentPlayerClass = PlayerCharacter ? PlayerCharacter->GetClass() : nullptr;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		if (Class->IsChildOf(APlayerCharacter::StaticClass()) && Class != CurrentPlayerClass)
		{
			TSubclassOf<APlayerCharacter> Subclass = Class;
			AvailablePlayerClasses.Add(Subclass);
		}
	}
	return AvailablePlayerClasses;
}
void AAdventureGameModeBase::SetNextPlayerClass(APlayerCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
		return;

	// Get the available player character classes
	TArray<TSubclassOf<APlayerCharacter>> AvailablePlayerClasses = GetAvailablePlayerClasses(PlayerCharacter);

	// Find the index of the current player's class in the available classes array
	int32 CurrentClassIndex = AvailablePlayerClasses.IndexOfByKey(PlayerCharacter->GetClass());

	if (CurrentClassIndex != INDEX_NONE)
	{
		// Calculate the index of the next class, wrapping around if needed
		int32 NextClassIndex = (CurrentClassIndex + 1) % AvailablePlayerClasses.Num();

		// Spawn a new player character of the next class
		ChangePlayerClass(PlayerCharacter, AvailablePlayerClasses[NextClassIndex]);
	}
}

void AAdventureGameModeBase::SetPreviousPlayerClass(APlayerCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
		return;

	// Get the available player character classes
	TArray<TSubclassOf<APlayerCharacter>> AvailablePlayerClasses = GetAvailablePlayerClasses(PlayerCharacter);

	// Find the index of the current player's class in the available classes array
	int32 CurrentClassIndex = AvailablePlayerClasses.IndexOfByKey(PlayerCharacter->GetClass());

	if (CurrentClassIndex != INDEX_NONE)
	{
		// Calculate the index of the previous class, wrapping around if needed
		int32 PreviousClassIndex = (CurrentClassIndex - 1 + AvailablePlayerClasses.Num()) % AvailablePlayerClasses.Num();

		// Spawn a new player character of the previous class
		ChangePlayerClass(PlayerCharacter, AvailablePlayerClasses[PreviousClassIndex]);
	}
}

void AAdventureGameModeBase::ChangePlayerClass(APlayerCharacter* PlayerCharacter, TSubclassOf<APlayerCharacter> NewPlayerCharacterClass)
{
	if (PlayerCharacter && NewPlayerCharacterClass)
	{
		// Preserve the current player's location and rotation
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FRotator PlayerRotation = PlayerCharacter->GetActorRotation();

		// Destroy the current player character
		PlayerCharacter->Destroy();

		// Spawn a new player character of the specified class
		APlayerCharacter* NewPlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(NewPlayerCharacterClass, PlayerLocation, PlayerRotation);
		if (NewPlayerCharacter)
		{
			// Possess the new player character
			APlayerController* NewPlayerController = Cast<APlayerController>(NewPlayerCharacter->GetController());
			if (NewPlayerController)
			{
				NewPlayerController->Possess(NewPlayerCharacter);
			}
		}

	
	}
}

void AAdventureGameModeBase::RemoveLastPlayer()
{
	if (PlayerControllers.Num() > 0)
	{
		APlayerController* LastPlayerController = PlayerControllers.Last();
		APlayerCharacter* LastPlayerCharacter = Players.Last();

		if (LastPlayerController && LastPlayerCharacter)
		{
			// Unpossess the player character
			LastPlayerController->UnPossess();

			// Destroy the player controller and character
			LastPlayerController->Destroy();
			LastPlayerCharacter->Destroy();

			// Remove from arrays
			AAdventurePlayerController* AdventurePlayerController = Cast<AAdventurePlayerController>(LastPlayerController);

			PlayerControllers.Remove(AdventurePlayerController);
			Players.Remove(LastPlayerCharacter);

			// Remove LocalPlayer to adjust split-screen settings
			UGameInstance* GameInstance = GetGameInstance();
			ULocalPlayer* LocalPlayer = LastPlayerController->GetLocalPlayer();

			if (GameInstance && LocalPlayer)
			{
				GameInstance->RemoveLocalPlayer(LocalPlayer);
			}
		}
	}
}

void AAdventureGameModeBase::StopGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (CurrentLevelName.IsNone())
		{
			CurrentLevelName = *World->GetMapName();
		}
		OpenLevel(CurrentLevelName);
	}
}

void AAdventureGameModeBase::PauseGame()
{

	for (TActorIterator<APlayerController> It(GetWorld()); It; ++It)
	{
		APlayerController* PlayerController = *It;
		PlayerController->SetPause(true);
	}
	for (APlayerCharacter* PlayerCharacter : Players)
	{
		// PlayerCharacter->SetGameInputMode(true);
	}
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
}

void AAdventureGameModeBase::ResumeGame()
{
	if (Started)
	{
		for (TActorIterator<APlayerController> It(GetWorld()); It; ++It)
		{
			APlayerController* PlayerController = *It;
			PlayerController->SetPause(false);
			//PlayerController->SetCinematicMode(false, false, false, false, false);
		}
		for (APlayerCharacter* PlayerCharacter : Players)
		{
			// PlayerCharacter->SetGameInputMode(false);
		}
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}

}

void AAdventureGameModeBase::ShownMenu()
{
	MenuVisible = true;
	PauseGame();
}

void AAdventureGameModeBase::CloseMenu()
{
	MenuVisible = false;
	ResumeGame();
}

void AAdventureGameModeBase::ShowInventar()
{
	InventarVisible = true;
	PauseGame();
}

void AAdventureGameModeBase::CloseInventar()
{
	InventarVisible = false;
	ResumeGame();
}

void AAdventureGameModeBase::ShowControls()
{
	ControlsVisible = true;
}

void AAdventureGameModeBase::CloseControls()
{
	ControlsVisible = false;
}

void AAdventureGameModeBase::GameOver(AGameCharacter* LooserCharacter, bool GameEnded)
{
	LooserCharacters.Add(LooserCharacter);
	GameOverCharacters.Add(LooserCharacter);
	if (InGameCharacters.Contains(LooserCharacter)) 
	{
		InGameCharacters.Remove(LooserCharacter);
	}
	if (GameEnded)
	{
		GameIsOver = true;
		PauseGame();
	}
}

void AAdventureGameModeBase::WinGame(AGameCharacter* WinnerCharacter, bool GameEnded)
{
	WinnerCharacters.Add(WinnerCharacter);
	GameOverCharacters.Add(WinnerCharacter);
	if (InGameCharacters.Contains(WinnerCharacter))
	{
		InGameCharacters.Remove(WinnerCharacter);
	}
	if (GameEnded)
	{
		GameIsOver = true;
		PauseGame();
	}
}

void AAdventureGameModeBase::StartGame()
{
	if (!Started) {
		Started = true;
		ResumeGame();
		OnStartGame.Broadcast();
	}
}

void AAdventureGameModeBase::RestartGame()
{
	GameIsOver = false;
	WinnerCharacters.Empty();
	LooserCharacters.Empty();
	RestartLevel();
	Started = false;
	PauseGame();
}

void AAdventureGameModeBase::RestartLevel()
{
	UWorld* World = GetWorld();
	if (World && !CurrentLevelName.IsNone())
	{
		OpenLevel(CurrentLevelName);
	}
}

void AAdventureGameModeBase::ShowInteraction(AInteractionActor* InteractionActor)
{
	CurrentInteractionActor = InteractionActor;
	InteractionVisible = true;

}

void AAdventureGameModeBase::CloseInteraction()
{
	InteractionVisible = false;
	ResumeGame();
}

void AAdventureGameModeBase::ShowTask(ATaskActor* TaskActor)
{
	CurrentTaskActor = TaskActor;
	TaskVisible = true;
	PauseGame();
}

void AAdventureGameModeBase::HideTask()
{
	TaskVisible = false;
	ResumeGame();
}

void AAdventureGameModeBase::ShowMap()
{
	MapVisible = true;
	PauseGame();
}

void AAdventureGameModeBase::HideMap()
{
	MapVisible = false;
	ResumeGame();
}

void AAdventureGameModeBase::AttachMapCamera(USpringArmComponent* MapCameraBoom)
{
	MapCameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	MapCameraBoom->SetupAttachment(RootComponent);

}
ASpeechBubble* AAdventureGameModeBase::CreateSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector Location, FRotator Rotation, FVector Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble> SpeechBubbleClass)
{
	return AddSpeechBubble(Text, FontSize, VisibilityDuration, &Location, &Rotation, &Scale, Actor, TargetCharacter, &SpeechBubbleClass);
}

ASpeechBubble* AAdventureGameModeBase::AddSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector* Location, FRotator* Rotation, FVector* Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble>* SpeechBubbleClass)
{
	TSubclassOf<ASpeechBubble> FinalSpeechBubbleClass;
	if (SpeechBubbleClass)
	{
		FinalSpeechBubbleClass = *SpeechBubbleClass;
	}
	if (!FinalSpeechBubbleClass)
	{
		FinalSpeechBubbleClass = DefaultSpeechBubbleClass;
	}
	if (FinalSpeechBubbleClass && FinalSpeechBubbleClass.Get())
	{
		UWorld* World = GetWorld();
		if (World)
		{
			ASpeechBubble* SpeechBubble = World->SpawnActor<ASpeechBubble>(FinalSpeechBubbleClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (SpeechBubble)
			{
				SpeechBubble->SpeechBubbleText = Text;
				SpeechBubble->SpeechBubbleFontSize = FontSize;
				if (VisibilityDuration > 0.0f)
				{
					SpeechBubble->VisibilityDuration = VisibilityDuration;
					SpeechBubble->HideAfterTime = true;
				}
				if (Actor)
				{
					SpeechBubble->AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform);
				}
				if (TargetCharacter) {
					SpeechBubble->TargetCharacter = TargetCharacter;
					SpeechBubble->TextFacesTarget = true;
				}
				SpeechBubble->SetActorRelativeLocation(*Location);
				SpeechBubble->SetActorRelativeRotation(*Rotation);
				SpeechBubble->SetActorScale3D(*Scale);
				return SpeechBubble;
			}
		}
	}
	return nullptr;
}



AAdventureCharacter* AAdventureGameModeBase::ActorIsChracter(AActor* Actor)
{
	return Cast<AAdventureCharacter>(Actor);;
}

