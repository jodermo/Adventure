#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "SpeechComponent.h"
#include "InteractionActor.generated.h"

class AAdventureCharacter;
class ATaskActor;
class AAnswerActor;
class AVehicle;

UCLASS(Blueprintable)
class ADVENTURE_API AInteractionActor : public AItemActor
{
    GENERATED_BODY()

public:
    AInteractionActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to show the interaction view."))
    bool ShowInteractionView = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to show the interaction view for all players in game."))
    bool ShowInteractionViewToAll = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "The character initiating the interaction."))
    AVehicle* Vehicle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "The character targeted by the interaction."))
    AAdventureCharacter* TargetCharacter;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to give an actor to the player."))
    bool GiveActor = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Append actor to character's actors list."))
    bool AppendActorToCharacter = false;



    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Give actor as an item to the player."))
    bool GiveActorAsItem = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Show interaction widget on interaction."))
    bool ShowInteraction = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Force interaction even if character is currently interacting."))
    bool ForceInteraction = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The interaction image to display."))
    UTexture2D* InteractionImage;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The title of the interaction."))
    FString InteractionTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The text of the interaction."))
    FString InteractionText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Adds TargetCharacter to IgnoreCharacters list."))
    bool IgnoreCharacter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Adds TargetCharacter to IgnoreCharacters list."))
    bool UnignoreCharacter = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether the interaction involves speaking to the actor."))
    bool SpeakToActor = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "Owning Character"))
    USpeechComponent* SpeechComponent;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to ask a question during interaction."))
    bool AskQuestion = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The question to ask during interaction."))
    FString InteractionQuestion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Stopps the game on interaction"))
    bool PauseGame = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to give items to the player during interaction."))
    bool GiveItems = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Array of item classes to give to the player during interaction."))
    TArray<TSubclassOf<AItemActor>> InteractionItemClasses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to trigger tasks during interaction."))
    bool TriggerTasks = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to trigger tasks during interaction."))
    bool TriggertTaskAfterAnother = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to apply damage to the character during interaction."))
    bool MakeDamage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Only apply damage once when interacting."))
    bool MakeDamageOnlyOnce = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Multiplier for the amount of damage to apply."))
    float DamageMultiplicator = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Indicates whether damage has been applied during interaction."))
    bool DidDamage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Determines whether to give points to the player during interaction."))
    bool GivePoints = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Only award points once when interacting."))
    bool GivePointsOnlyOnce = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Number of points to give to the player during interaction."))
    int PointsToGive = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Indicates whether points have been awarded during interaction."))
    bool AwardedPoints = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Array of task classes to trigger during interaction."))
    TArray<TSubclassOf<ATaskActor>> InteractionTaskClasses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Array of added tasks."))
    TArray<ATaskActor*> InteractionTasks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The component used for interaction answers."))
    UStaticMeshComponent* InteractionTaskMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Index of current triggered task"))
    int CurrentTasksIndex = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Index for next task to trigger"))
    int NextTasksIndex = 0;

    UFUNCTION(BlueprintCallable, Category = "Interaction Actor", meta = (ToolTip = "Select next Task, based on current task index"))
    void TriggerNextTask();

    UFUNCTION(BlueprintCallable, Category = "Interaction Actor", meta = (ToolTip = "Select task based on given index"))
    void TriggerTask(float TasksIndex);

    UFUNCTION(BlueprintCallable, Category = "Interaction Actor", meta = (ToolTip = "TriggerInteractionClass"))
    void TriggerInteractionClass(AAdventureCharacter* FromCharacter, AAdventureCharacter* ToCharacter, TSubclassOf<AInteractionActor> NewInteractionActorClass);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "Array of answer classes for this interaction actor."))
    TArray<TSubclassOf<AAnswerActor>> InteractionAnswerClasses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Array of added answers."))
    TArray<AAnswerActor*> InteractionAnswers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Actor", meta = (ToolTip = "The component used for interaction answers."))
    UStaticMeshComponent* InteractionAnswerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Selected Answer, when Character has choosen one answer."))
    AAnswerActor* SelectedAnswer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Actor", meta = (ToolTip = "Selected Answer, when Character has choosen one answer."))
    AInteractionActor* ParentInteractionActor;

    void CreateAnswers();


    UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuDeny"))
    void AcceptInteraction();

    UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "MenuDeny"))
    void DenyInteraction();


    virtual void SetCharacter(AAdventureCharacter* ItemCharacter) override;


protected:
    virtual void BeginPlay() override;


public:
    virtual void Tick(float DeltaTime) override;
};
