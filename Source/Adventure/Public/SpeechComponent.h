#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RhubarbPhonemeStructs.h"

#include "SpeechComponent.generated.h"


class ASpeechBubble;
class AGameCharacter;
class AAdventureCharacter;

UCLASS(Blueprintable)
class ADVENTURE_API USpeechComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USpeechComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (ToolTip = ""))
	AGameCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (ToolTip = ""))
	AAdventureCharacter* CurrentTargetCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = ""))
	bool TriggerAudio = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (ToolTip = ""))
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = ""))
	bool UseRhubarb = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RhubarbPhonemes", Meta = (RequiredAssetDataTags = "RowStructure=/Script/Adventure.RhubarbPhonemeData"))
	FDataTableRowHandle RhubarbPhonemeData;

	FRhubarbPhonemeData CurrentRhubarbPhonemeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = ""))
	bool ShowSpeechBubble = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = ""))
	TSubclassOf<ASpeechBubble> DefaultSpeechBubbleClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = ""))
	FString SpeechBubbleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = "ShowSpeechBubbleTextSize"))
	float ShowSpeechBubbleTextSize = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubble", meta = (ToolTip = "ShowSpeechBubbleTime"))
	float ShowSpeechBubbleDuration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubbler", meta = (ToolTip = "SpeechBubbleLocation"))
	FVector SpeechBubbleLocation = FVector(0.0f, -100.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubbler", meta = (ToolTip = "SpeechBubbleRotation"))
	FRotator SpeechBubbleRotation = FRotator(0.0f, 90.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeechBubbler", meta = (ToolTip = "SpeechBubbleScale"))
	FVector SpeechBubbleScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpeechBubbler", meta = (ToolTip = "CurrentSpeechBubble"))
	ASpeechBubble* CurrentSpeechBubble;



	UFUNCTION(BlueprintCallable, Category = "SpeechBubbler", meta = (ToolTip = "ShowSpeechBuuble"))
	void CreateSpeechBuuble(FString Text, float FontSize, float Duration);

	UFUNCTION(BlueprintCallable, Category = "SpeechBubbler", meta = (ToolTip = ""))
	void SpeakToCharacter(AAdventureCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "SpeechBubbler", meta = (ToolTip = ""))
	void Speak();



protected:
	virtual void BeginPlay() override;

	virtual void InitSpeechComponent();

	virtual ASpeechBubble* AddSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector* Location, FRotator* Rotation, FVector* Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble>* SpeechBubbleClass);


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
