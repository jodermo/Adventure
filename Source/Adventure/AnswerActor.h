
#pragma once

#include "CoreMinimal.h"
#include "InteractionActor.h"
#include "TaskArea.h"
#include "AnswerActor.generated.h"


class AAdventureCharacter;
class AItemActor;
class ATaskActor;

UCLASS(Blueprintable)
class ADVENTURE_API AAnswerActor : public AInteractionActor
{
	GENERATED_BODY()
	
public:	
	AAnswerActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Answer", meta = (ToolTip = "The image associated with this answer."))
	UTexture2D* AnswerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Answer", meta = (ToolTip = "The title of this answer."))
	FString AnswerTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Answer", meta = (ToolTip = "The text content of this answer."))
	FString AnswerText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Answer", meta = (ToolTip = "A detailed description of this answer."))
	FString AnswerDescription;
	

	UFUNCTION(BlueprintCallable, Category = "Interaction Answer", meta = (ToolTip = "Triggers this answer"))
	void TriggerAnswer(AAdventureCharacter* QuestionCharacter, AAdventureCharacter* AnswerCharacter);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction Answer")
	void OnAnswerTriggered();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

};
