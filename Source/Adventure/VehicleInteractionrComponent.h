#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionActor.h"
#include "Logging.h"
#include "VehicleInteractionrComponent.generated.h"



class AVehicle;
class AAdventureCharacter;
class ANonPlayerCharacter;
class APlayerCharacter;
class AEnvironmentalObject;

UCLASS(Blueprintable)
class ADVENTURE_API UVehicleInteractionrComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVehicleInteractionrComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "The logger associated with this interaction component."))
	ULogging* Logger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (ToolTip = "The owner actor of this interaction component."))
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (ToolTip = "The top-down character associated with this interaction component."))
	AVehicle* Vehicle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle", meta = (ToolTip = "ShowInteraction."))
	bool EnterVehicle = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle", meta = (ToolTip = "ShowInteraction."))
	bool TriggerInteraction = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Points", meta = (ToolTip = "Enable awarding points for this character interaction component."))
	bool GivePoints = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Points", meta = (ToolTip = "Only award points once when interacting."))
	bool GivePointsOnlyOnce = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Points", meta = (ToolTip = "Remove points after they are given."))
	bool RemovePointsAfterGiven = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Points", meta = (ToolTip = "Number of points to award during interaction."))
	int PointsToGive = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle Points", meta = (ToolTip = "Indicates whether points were already awarded during interaction."))
	bool AwardedPoints = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Interaction", meta = (ToolTip = "Array of interaction actor classes for this character interaction component."))
	TArray<TSubclassOf<AInteractionActor>> InteractionActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Interaction", meta = (ToolTip = "Index of the current interaction in the array."))
	int CurrentInteractionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Interaction", meta = (ToolTip = "Index of the next interaction in the array."))
	int NextInteractionIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle Interaction", meta = (ToolTip = "Index of the interaction to trigger in the array."))
	int TriggerInteractionIndex = 0;


	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Perform a character interaction with the target character."))
	virtual void DoObjectInteraction(AEnvironmentalObject* EnvironmentalObject, float DeltaTime);



	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Perform a character interaction with the target character."))
	virtual void DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Perform a character interaction with the target character."))
	virtual void TriggerInteractionActor(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Perform a character-to-actor interaction with the target character."))
	virtual void DoCharacterActorInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Handle the character interaction with the target character."))
	virtual void OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Interaction", meta = (ToolTip = "Handle the character-to-actor interaction with the target character and interaction actor."))
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
