#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialParameterCollection.h"
#include "Components/StaticMeshComponent.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include "aquila/aquila.h"
#include "aquila/global.h"
#include "aquila/transform.h"
#include "aquila/source/WaveFile.h"
#include "aquila/tools/TextPlot.h"
#include "aquila/transform/Mfcc.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/transform/FFT.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "RhubarbPhonemeStructs.h"
#include "Engine/DataTable.h"
#include "AudioAnalyserComponent.generated.h"


class AGameCharacter;




UCLASS(Blueprintable)
class ADVENTURE_API UAudioAnalyserComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UAudioAnalyserComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (RequiredAssetDataTags = "RowStructure=/Script/Adventure.RhubarbPhonemeData"))
	TObjectPtr<UDataTable> DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (RequiredAssetDataTags = "RowStructure=/Script/Adventure.RhubarbPhonemeData"))
	FDataTableRowHandle RhubarbPhonemeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "AudioComponent"))
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "MouthDynamicMaterial"))
	UMaterialInstance* MouthMaterial;

	UPROPERTY();
	UMaterialInstanceDynamic* DynamicMouthMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "Owning Character"))
	AGameCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "Detected Phonemes"))
	TArray<FAudioPhoneme> Phonemes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "DetectAmplitude"))
	bool DetectAmplitude = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "DetectPhonemes"))
	bool DetectEnvelope = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "DetectPhonemes"))
	bool DetectRhubarbPhonemes = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "..."))
	float PhonemesAmplitudeChangeLevel = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float SampleAmplitudeFactor = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float MaxAmplitude = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float CurrtentAmplitude = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
    TArray<float> CurrtentEnvelope;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentSample = 0;

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Get Rhubarb Phoneme By Percent"))
	FRhubarbPhonemeCue GetRhubarbPhonemeByTime(float PlaybackPercent);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	FRhubarbAudio CurrentRhubarbAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	TArray<FRhubarbPhonemeCue> CurrentRhubarbPhonemes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	FRhubarbPhonemeCue CurrentRhubarbPhoneme;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	FAudioPhoneme CurrentPhoneme;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentBytesPerSample = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentNumChannels = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentSampleRate = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float CurrentDuration = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float CurrentTime = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentTotalSamples = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	int CurrentSampleIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	float PercentPlayed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Analyser", meta = (ToolTip = "Current Sound Wave"))
	TArray<uint8> CurrentAudioData;

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void SetRhubarbAudioData(FRhubarbAudio RhubarbAudio);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void PlayRhubarbAudioData(FRhubarbAudio RhubarbAudio);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void SetAudioComponent(UAudioComponent* AudioComponentToAnalyze);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void PlayAudioComponent(UAudioComponent* AudioComponentToAnalyze);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void SetRhubarbPhonemes(TArray<FRhubarbPhonemeCue> RhubarbPhonemes);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	void Play();

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	UStaticMeshComponent* CreatePhonemeMaterial(UStaticMeshComponent* StaticMesh, FAudioPhoneme AudioPhoneme);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "MakeRandomPhonemeMaterial"))
	FAudioPhoneme SetRhubarbPhoneme(FRhubarbPhonemeCue NewRhubarbPhoneme);

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "MakeRandomPhonemeMaterial"))
	FAudioPhoneme MakeRandomCharacterPhoneme();

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	FAudioPhoneme GetRandomPhoneme();

	UFUNCTION(BlueprintCallable, Category = "Audio Analyser", meta = (ToolTip = "Analyze Current Sound"))
	FAudioPhoneme FindPhonemeByValue(FString PhonemeValue);

	UFUNCTION(BlueprintNativeEvent, Category = "Speech Recognition")
	void OnAmplitudeChange(float AmplitudeValue);

	UFUNCTION(BlueprintNativeEvent, Category = "Speech Recognition")
	void OnEnvelopeChange(const TArray<float>& Envelope);

	UFUNCTION(BlueprintNativeEvent, Category = "Speech Recognition")
	void OnPhonemeChange(FAudioPhoneme Phoneme);

	virtual void InitAnalyzer();

protected:

	virtual void BeginPlay() override;



private:

	UFUNCTION()
	void OnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent);

	void SetAmplitude(float NewAmplitudeLevel);
	void SetEnvelope(const TArray<float>& Envelope);

	int16 ExtractSample(const uint8* RawAudioData, int32 SampleIndex, int32 BytesPerSample);

	static TArray<uint8> SoundWaveToBytes(const USoundWave* Audio);
	static TArray<uint8> FStringToBytes(const FString& String);
	static TArray<uint8> uint32ToBytes(const uint32 Value, bool UseLittleEndian = true);
	static TArray<uint8> uint16ToBytes(const uint16 Value, bool UseLittleEndian = true);



	TArray<FRhubarbPhonemeCue> LoadRhubarbJSONFile(FString FilePath);

	float CalculateSpectralCentroid(const std::vector<Aquila::SampleType>& audioData, int SampleRate);
	float CalculateSpectralFlux(const std::vector<Aquila::SampleType>& audioData, int SampleRate);
	std::vector<float> CalculateEnvelope(const std::vector<Aquila::SampleType>& audioData);
	std::vector<Aquila::ComplexType> CalculateFFT(const std::vector<Aquila::SampleType>& audioData);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
