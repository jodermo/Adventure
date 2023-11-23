#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeechRecognitionComponent.generated.h"

UCLASS(Blueprintable)
class ADVENTURE_API USpeechRecognitionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpeechRecognitionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Recognition", meta = (ToolTip = "Name of the character"))
	USoundWave* SoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Recognition", meta = (ToolTip = "Name of the character"))
	FString DetectedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Recognition", meta = (ToolTip = "Name of the character"))
	FString ErrorMessage;

	UFUNCTION(BlueprintCallable, Category = "Speech Recognition", meta = (ToolTip = "Detect Speech Sounds"))
	void DetectSounds(UAudioComponent* AudioComponent);

	UFUNCTION()
	void SetDetectedSound(FString Sound);

	UFUNCTION(BlueprintNativeEvent, Category = "Speech Recognition")
	void OnDetectSound(const FString& Sound);

	UFUNCTION()
	void SetDetectedError(FString Message);

	UFUNCTION(BlueprintNativeEvent, Category = "Speech Recognition")
	void OnDetectError(const FString& Message);

protected:
	virtual void BeginPlay() override;


private:
	FTimerHandle TimerHandle;
	void ReadRhubarbOutput();
	void OnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent);


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
