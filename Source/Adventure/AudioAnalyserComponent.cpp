
#include "AudioAnalyserComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameCharacter.h"
#include <vector>
#include <cmath>
#include "Engine/Engine.h"

UAudioAnalyserComponent::UAudioAnalyserComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bTickEvenWhenPaused = true;
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    MouthMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("MouthMaterial"));
    DynamicMouthMaterial = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("DynamicMouthMaterial"));
    InitAnalyzer();
}

void UAudioAnalyserComponent::BeginPlay()
{
	Super::BeginPlay();
    InitAnalyzer();
}

void UAudioAnalyserComponent::InitAnalyzer()
{
    if (!Character && GetOwner())
    {
        Character = Cast<AGameCharacter>(GetOwner());
    }
}

void UAudioAnalyserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FAudioPhoneme UAudioAnalyserComponent::FindPhonemeByValue(FString PhonemeValue)
{
    for (const FAudioPhoneme& Phoneme : Phonemes)
    {
        if (Phoneme.Value == PhonemeValue)
        {
            return Phoneme;
        }
    }
    return FAudioPhoneme();
}

FAudioPhoneme UAudioAnalyserComponent::GetRandomPhoneme()
{
    if (Phonemes.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, Phonemes.Num() - 1);
        return Phonemes[RandomIndex];
    }
    return FAudioPhoneme();
}

UStaticMeshComponent* UAudioAnalyserComponent::CreatePhonemeMaterial(UStaticMeshComponent* StaticMesh, FAudioPhoneme AudioPhoneme)
{
    if (MouthMaterial && StaticMesh && AudioPhoneme.MouthImage)
    {
        DynamicMouthMaterial = UMaterialInstanceDynamic::Create(MouthMaterial, this);
        DynamicMouthMaterial->SetTextureParameterValue(FName(TEXT("MouthImage")), AudioPhoneme.MouthImage);
        StaticMesh->SetMaterial(0, DynamicMouthMaterial);
    }
    return StaticMesh;
}

TArray<FRhubarbPhonemeCue> UAudioAnalyserComponent::LoadRhubarbJSONFile(FString FilePath)
{
    FilePath = FPaths::ProjectContentDir() + FilePath;
    FString FileContent;
    TArray<FRhubarbPhonemeCue> ResultPhonemes;
    if (FPaths::FileExists(FilePath))
    {
        FFileHelper::LoadFileToString(FileContent, *FilePath);
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContent);
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            TSharedPtr<FJsonObject> MetadataObject = JsonObject->GetObjectField("metadata");
            FString SoundFile = MetadataObject->GetStringField("soundFile");
            double Duration = MetadataObject->GetNumberField("duration");
            TArray<TSharedPtr<FJsonValue>> MouthCues = JsonObject->GetArrayField("mouthCues");
            for (TSharedPtr<FJsonValue> Value : MouthCues)
            {
                TSharedPtr<FJsonObject> MouthCueObject = Value->AsObject();
                double Start = MouthCueObject->GetNumberField("start");
                double End = MouthCueObject->GetNumberField("end");
                FString MouthValue = MouthCueObject->GetStringField("value");
                FRhubarbPhonemeCue RhubarbPhoneme = { Start, End, MouthValue };
                ResultPhonemes.Add(RhubarbPhoneme);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to parse the JSON file."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("File not found: %s"), *FilePath);
    }
    return ResultPhonemes;
}

void UAudioAnalyserComponent::SetRhubarbAudioData(FRhubarbAudio RhubarbAudio)
{
    SetRhubarbPhonemes(RhubarbAudio.RhubarbPhonemeData.MouthCues);
    SetAudioComponent(RhubarbAudio.AudioComponent);
}

void UAudioAnalyserComponent::PlayRhubarbAudioData(FRhubarbAudio RhubarbAudio)
{
    SetRhubarbPhonemes(RhubarbAudio.RhubarbPhonemeData.MouthCues);
    PlayAudioComponent(RhubarbAudio.AudioComponent);
}

void UAudioAnalyserComponent::PlayAudioComponent(UAudioComponent* AudioComponentToAnalyze)
{
    SetAudioComponent(AudioComponentToAnalyze);
    Play();
}

void UAudioAnalyserComponent::SetAudioComponent(UAudioComponent* AudioComponentToAnalyze)
{
    if (AudioComponent)
    {
        AudioComponent->OnAudioPlaybackPercent.RemoveDynamic(this, &UAudioAnalyserComponent::OnAudioPlaybackPercent);
    }
    AudioComponent = AudioComponentToAnalyze;
    if (AudioComponent)
    {
        AudioComponent->OnAudioPlaybackPercent.AddDynamic(this, &UAudioAnalyserComponent::OnAudioPlaybackPercent);
    }
}

void UAudioAnalyserComponent::SetRhubarbPhonemes(TArray<FRhubarbPhonemeCue> RhubarbPhonemes)
{
    CurrentRhubarbPhonemes = RhubarbPhonemes;
}

void UAudioAnalyserComponent::Play()
{
    if (AudioComponent)
    {
        AudioComponent->Play();
    }
}

TArray<uint8> UAudioAnalyserComponent::SoundWaveToBytes(const USoundWave* Audio)
{
    TArray<uint8> BytesArr;
    if (IsValid(Audio))
    {
        TArray<uint8> AudioBytes;
        TArray<uint8> AudioHeader;
        uint32 SampleRate;
        uint16 BitDepth = 16;
        uint16 Channels;
        if (Audio->GetImportedSoundWaveData(AudioBytes, SampleRate, Channels))
        {
            AudioHeader.Append(FStringToBytes("RIFF"));								// 1-4
            AudioHeader.Append(uint32ToBytes(AudioBytes.Num() + 36));					// 5-8
            AudioHeader.Append(FStringToBytes("WAVEfmt "));							// 9-16
            AudioHeader.Append(uint32ToBytes(16));										// 17-20
            AudioHeader.Append(uint16ToBytes(1));									// 21-22
            AudioHeader.Append(uint16ToBytes(Channels));								// 23-24
            AudioHeader.Append(uint32ToBytes(SampleRate));									// 25-28
            AudioHeader.Append(uint32ToBytes(SampleRate * BitDepth * Channels / 8));	// 29-32
            AudioHeader.Append(uint16ToBytes(BitDepth * Channels / 8));			// 33-34
            AudioHeader.Append(uint16ToBytes(BitDepth));								// 35-36
            AudioHeader.Append(FStringToBytes("data"));								// 37-40
            AudioHeader.Append(uint32ToBytes(AudioBytes.Num()));						// 41-44
            BytesArr.Append(AudioHeader);
            BytesArr.Append(AudioBytes);
        }
    }
    return BytesArr;
}

TArray<uint8> UAudioAnalyserComponent::FStringToBytes(const FString& String)
{
    TArray<uint8> OutBytes;
    if (String.Len() > 0)
    {
        FTCHARToUTF8 Converted(*String);
        OutBytes.Append(reinterpret_cast<const uint8*>(Converted.Get()), Converted.Length());
    }
    return OutBytes;
}

TArray<uint8> UAudioAnalyserComponent::uint32ToBytes(const uint32 Value, bool UseLittleEndian)
{
    TArray<uint8> OutBytes;
    if (UseLittleEndian)
    {
        OutBytes.Add(Value >> 0 & 0xFF);
        OutBytes.Add(Value >> 8 & 0xFF);
        OutBytes.Add(Value >> 16 & 0xFF);
        OutBytes.Add(Value >> 24 & 0xFF);
    }
    else
    {
        OutBytes.Add(Value >> 24 & 0xFF);
        OutBytes.Add(Value >> 16 & 0xFF);
        OutBytes.Add(Value >> 8 & 0xFF);
        OutBytes.Add(Value >> 0 & 0xFF);
    }
    return OutBytes;
}

TArray<uint8> UAudioAnalyserComponent::uint16ToBytes(const uint16 Value, bool UseLittleEndian)
{
    TArray<uint8> OutBytes;
    if (UseLittleEndian)
    {
        OutBytes.Add(Value >> 0 & 0xFF);
        OutBytes.Add(Value >> 8 & 0xFF);
    }
    else
    {
        OutBytes.Add(Value >> 8 & 0xFF);
        OutBytes.Add(Value >> 0 & 0xFF);
    }
    return OutBytes;
}

void UAudioAnalyserComponent::OnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, float PlaybackPercent)
{
    CurrtentAmplitude = 0.0f;
    if (!PlayingSoundWave)
    {
        return;
    }
    float Percent = FMath::Clamp(PlaybackPercent, 0.0f, 1.0f);
    PercentPlayed = Percent * 100.0f;
    const int64 SampleRate = PlayingSoundWave->GetSampleRateForCurrentPlatform();
    CurrentSampleRate = SampleRate;
    const int32 Channels = PlayingSoundWave->NumChannels;
    CurrentNumChannels = Channels;
    const float Duration = PlayingSoundWave->GetDuration();
    CurrentDuration = Duration;
    float PlaybackTime = Duration * PlaybackPercent;
    CurrentTime = PlaybackTime;
    const int32 TotalSamples = FMath::Max(1, static_cast<int32>(Duration * SampleRate));
    CurrentTotalSamples = TotalSamples;
    const int32 SampleIndex = FMath::RoundToInt(Percent * (TotalSamples - 1));
    CurrentSampleIndex = SampleIndex;
    const int32 BytesPerSample = 2;
    CurrentBytesPerSample = BytesPerSample;
    TArray<uint8> RawAudioData = SoundWaveToBytes(PlayingSoundWave);
    CurrentAudioData = RawAudioData;
    if (RawAudioData.Num() && BytesPerSample == 2)
    {
        CurrentSample = *reinterpret_cast<const int16*>(RawAudioData.GetData() + SampleIndex * BytesPerSample);
    }
    else if (RawAudioData.Num() && BytesPerSample == 1)
    {
        int16 RawSample = static_cast<int16>(RawAudioData[SampleIndex * BytesPerSample]);
        CurrentSample = RawSample << 8;
    }
    if (CurrentSample && DetectAmplitude)
    {
        float NormalizedAmplitude = static_cast<float>(CurrentSample) * SampleAmplitudeFactor;
        SetAmplitude(NormalizedAmplitude);
    }
    if (CurrentSample && DetectEnvelope) {
        std::vector<Aquila::SampleType> audioData;
        audioData.reserve(RawAudioData.Num() / sizeof(Aquila::SampleType));
        for (int32 i = 0; i < RawAudioData.Num(); i += sizeof(Aquila::SampleType))
        {
            Aquila::SampleType sampleValue = *reinterpret_cast<const Aquila::SampleType*>(&RawAudioData[i]);
            audioData.push_back(sampleValue);
        }
        auto signalSource = Aquila::SignalSource(audioData, SampleRate);
        std::vector<float> Envelope = CalculateEnvelope(audioData);
        TArray<float> EnvelopeArray;
        EnvelopeArray.SetNumUninitialized(Envelope.size());
        FMemory::Memcpy(EnvelopeArray.GetData(), Envelope.data(), Envelope.size() * sizeof(float));
        SetEnvelope(EnvelopeArray);
    }

    if (DetectRhubarbPhonemes) {
        FRhubarbPhonemeCue NewtRhubarbPhoneme = GetRhubarbPhonemeByTime(PlaybackTime);
        SetRhubarbPhoneme(NewtRhubarbPhoneme);
    }
}

FRhubarbPhonemeCue UAudioAnalyserComponent::GetRhubarbPhonemeByTime(float PlaybackTime)
{
    FRhubarbPhonemeCue RhubarbPhoneme;
    for (const FRhubarbPhonemeCue& Phoneme : CurrentRhubarbPhonemes)
    {
        if (PlaybackTime >= Phoneme.Start && PlaybackTime <= Phoneme.End)
        {
            RhubarbPhoneme = Phoneme;
            break; 
        }
    }
    return RhubarbPhoneme;
}

int16 UAudioAnalyserComponent::ExtractSample(const uint8* RawAudioData, int32 SampleIndex, int32 BytesPerSample)
{
    if (BytesPerSample == 2)
    {
        return *reinterpret_cast<const int16*>(RawAudioData + SampleIndex * BytesPerSample);
    }

    return 0;
}

void UAudioAnalyserComponent::SetEnvelope(const TArray<float>& NewEnvelopeValue)
{
    if (CurrtentEnvelope != NewEnvelopeValue)
    {
        CurrtentEnvelope = NewEnvelopeValue;
        OnEnvelopeChange(CurrtentEnvelope);
    }
}

void UAudioAnalyserComponent::SetAmplitude(float NewAmplitudeLevel)
{
    NewAmplitudeLevel = FMath::Abs(NewAmplitudeLevel);
    if (NewAmplitudeLevel > MaxAmplitude)
    {
        NewAmplitudeLevel = MaxAmplitude;
    }
    if (CurrtentAmplitude != NewAmplitudeLevel)
    {
        CurrtentAmplitude = NewAmplitudeLevel;
        OnAmplitudeChange(CurrtentAmplitude);
    }
}

FAudioPhoneme UAudioAnalyserComponent::SetRhubarbPhoneme(FRhubarbPhonemeCue NewRhubarbPhoneme)
{
    CurrentRhubarbPhoneme = NewRhubarbPhoneme;
    if (NewRhubarbPhoneme.Value != CurrentPhoneme.Value && !NewRhubarbPhoneme.Value.IsEmpty()) {
        CurrentPhoneme = FindPhonemeByValue(NewRhubarbPhoneme.Value);
        if (CurrentPhoneme.MouthImage)
        {
            CreatePhonemeMaterial(Character->MouthMesh, CurrentPhoneme);
        }
        OnPhonemeChange(CurrentPhoneme);
        return CurrentPhoneme;
    }
    return FAudioPhoneme();
}

FAudioPhoneme UAudioAnalyserComponent::MakeRandomCharacterPhoneme()
{

    FAudioPhoneme RandomPhoneme = GetRandomPhoneme();
    if (Character)
    {
        if (RandomPhoneme.MouthImage)
        {
            CreatePhonemeMaterial(Character->MouthMesh, RandomPhoneme);
        }
    }
    OnPhonemeChange(RandomPhoneme);
    return RandomPhoneme;
}

void UAudioAnalyserComponent::OnAmplitudeChange_Implementation(float AmplitudeValue)
{
    // This function can be implemented in Blueprints
}

void UAudioAnalyserComponent::OnEnvelopeChange_Implementation(const TArray<float>& Envelope)
{
    // This function can be implemented in Blueprints
}

void UAudioAnalyserComponent::OnPhonemeChange_Implementation(FAudioPhoneme Phoneme)
{
    // This function can be implemented in Blueprints
}

std::vector<float> UAudioAnalyserComponent::CalculateEnvelope(const std::vector<Aquila::SampleType>& audioData)
{
    int N = audioData.size();
    std::vector<float> envelope(N);
    for (int i = 0; i < N; ++i)
    {
        envelope[i] = std::abs(audioData[i]);
    }
    return envelope;
}





