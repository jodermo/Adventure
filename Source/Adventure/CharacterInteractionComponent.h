#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionActor.h"
#include "Logging.h"
#include "CharacterInteractionComponent.generated.h"




class AAdventureCharacter;
class ANonPlayerCharacter;
class APlayerCharacter;

UCLASS(Blueprintable)
class ADVENTURE_API UCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterInteractionComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "The logger associated with this interaction component."))
	ULogging* Logger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (ToolTip = "The owner actor of this interaction component."))
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (ToolTip = "The top-down character associated with this interaction component."))
	AAdventureCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (ToolTip = "The non-player character associated with this interaction component."))
	ANonPlayerCharacter* NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (ToolTip = "The player character associated with this interaction component."))
	APlayerCharacter* Player;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage", meta = (ToolTip = "Enable damage behavior for this character interaction component."))
	bool MakeDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage", meta = (ToolTip = "Only apply damage once when interacting."))
	bool MakeDamageOnlyOnce = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage", meta = (ToolTip = "Multiplier for the damage to apply during interaction."))
	float DamageMultiplicator = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Damage", meta = (ToolTip = "Indicates whether damage was already applied during interaction."))
	bool DidDamage = false;

	// ... Other properties ...

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Points", meta = (ToolTip = "Enable awarding points for this character interaction component."))
	bool GivePoints = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Points", meta = (ToolTip = "Only award points once when interacting."))
	bool GivePointsOnlyOnce = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Points", meta = (ToolTip = "Remove points after they are given."))
	bool RemovePointsAfterGiven = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Points", meta = (ToolTip = "Number of points to award during interaction."))
	int PointsToGive = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Points", meta = (ToolTip = "Indicates whether points were already awarded during interaction."))
	bool AwardedPoints = false;

	// ... Other properties ...

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Interaction", meta = (ToolTip = "Array of interaction actor classes for this character interaction component."))
	TArray<TSubclassOf<AInteractionActor>> InteractionActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Interaction", meta = (ToolTip = "Index of the current interaction in the array."))
	int CurrentInteractionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Interaction", meta = (ToolTip = "Index of the next interaction in the array."))
	int NextInteractionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Interaction", meta = (ToolTip = "Index of the interaction to trigger in the array."))
	int TriggerInteractionIndex = 0;

	// ... Other functions ...

	UFUNCTION(BlueprintCallable, Category = "Character Interaction", meta = (ToolTip = "Perform a character interaction with the target character."))
	virtual void DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Character Interaction", meta = (ToolTip = "Perform a character-to-actor interaction with the target character."))
	virtual void DoCharacterActorInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Character Interaction", meta = (ToolTip = "Handle the character interaction with the target character."))
	virtual void OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Character Interaction", meta = (ToolTip = "Handle the character-to-actor interaction with the target character and interaction actor."))
	virtual void OnCharacterActorInteraction(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor, float DeltaTime);

private:
	virtual void InitComponent();
	

protected:

	virtual void OnConstruction(const FTransform& Transform);

	virtual void BeginPlay() override;

	int32 CurrentConversationNodeIndex = 0;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
