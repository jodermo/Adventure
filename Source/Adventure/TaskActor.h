
#pragma once

#include "CoreMinimal.h"
#include "InteractionActor.h"
#include "TaskArea.h"
#include "TaskActor.generated.h"

class AAdventureCharacter;


UCLASS(Blueprintable)
class ADVENTURE_API ATaskActor : public AInteractionActor
{
	GENERATED_BODY()
	
public:	
	ATaskActor();



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Target Area", meta = (ToolTip = "Item has to be found by character"))
	TSubclassOf<ATaskArea> TargetAreaClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Target Area", meta = (ToolTip = "Item has to be found by character"))
	TArray<ATaskArea*> TargetAreas;


	UFUNCTION(BlueprintCallable, Category = "Task Target Area")
	void TriggerCharacterTask(AAdventureCharacter* ForCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Target Area", meta = (ToolTip = "Show areas on task interaction, hides areas on begin play"))
	bool ShowAreasOnTaskInteraction;


	UFUNCTION(BlueprintCallable, Category = "Task Target Area")
	TArray<ATaskArea*> FindTargetAreas();




protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
