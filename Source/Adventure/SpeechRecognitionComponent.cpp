
#include "SpeechRecognitionComponent.h"

USpeechRecognitionComponent::USpeechRecognitionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpeechRecognitionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USpeechRecognitionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpeechRecognitionComponent::DetectSounds(UAudioComponent* AudioComponent)
{
    if (!AudioComponent)
    {
        SetDetectedError(TEXT("AudioComponent is null."));
        return;
    }

    // Detect Sounds...
   
}




void USpeechRecognitionComponent::ReadRhubarbOutput()
{
    FString OutputFilePath = FPaths::ProjectSavedDir() + TEXT("rhubarb_output.txt");
    FString RhubarbOutput;
    if (FFileHelper::LoadFileToString(RhubarbOutput, *OutputFilePath))
    {
        OnDetectSound(RhubarbOutput);
    }
    else
    {
        OnDetectError(TEXT("Failed to read the output file"));
        return;
    }
}


void USpeechRecognitionComponent::SetDetectedSound(FString Sound)
{
    DetectedSound = Sound;
    ErrorMessage = "";
    OnDetectSound(Sound);
}

void USpeechRecognitionComponent::SetDetectedError(FString Message)
{
    DetectedSound = "";
    ErrorMessage = ErrorMessage;
    OnDetectError(ErrorMessage);
}

void USpeechRecognitionComponent::OnDetectSound_Implementation(const FString & Sound)
{
    // This function can be implemented in Blueprints
}

void USpeechRecognitionComponent::OnDetectError_Implementation(const FString & Message)
{
    // This function can be implemented in Blueprints
}
