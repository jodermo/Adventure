
#include "SpeechComponent.h"
#include "../SpeechBubble.h"
#include "../GameCharacter.h"
#include "../AdventureCharacter.h"
#include "Engine/Engine.h"

USpeechComponent::USpeechComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	InitComponent();
}

void USpeechComponent::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
}

void USpeechComponent::InitComponent()
{
	if (GetOwner())
	{
		USceneComponent* ParentCompoenent = GetOwner()->GetRootComponent();
		if (ParentCompoenent)
		{
			AudioComponent->AttachToComponent(ParentCompoenent, FAttachmentTransformRules::KeepRelativeTransform);
		}
		Character = Cast<AGameCharacter>(GetOwner());
	}
}


void USpeechComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USpeechComponent::SpeakToCharacter(AAdventureCharacter* TargetCharacter)
{
	CurrentTargetCharacter = TargetCharacter;
	Speak();
}

void USpeechComponent::Speak()
{
	if (ShowSpeechBubble)
	{
		CreateSpeechBuuble(SpeechBubbleText, ShowSpeechBubbleTextSize, ShowSpeechBubbleDuration);
	}
	if (TriggerAudio && AudioComponent)
	{

		if (UseRhubarb && !RhubarbPhonemeData.IsNull()) 
		{

			if (RhubarbPhonemeData.DataTable != nullptr) 
			{
				static const FString ContextString(TEXT("Rhubarb Phoneme Data Lookup"));
				const FRhubarbPhonemeData* TempPhonemeData = RhubarbPhonemeData.DataTable->FindRow<FRhubarbPhonemeData>(RhubarbPhonemeData.RowName, ContextString);
				if (TempPhonemeData != nullptr)
				{
					CurrentRhubarbPhonemeData = *TempPhonemeData;
				}
			}
			if (Character)
			{
				if (!Character->AudioAnalyser->Character)
				{
					Character->AudioAnalyser->Character = Character;
				}
				if (Character && CurrentRhubarbPhonemeData.MouthCues.Num())
				{
					const TArray<FRhubarbPhonemeCue> RhubarbPhonemes = CurrentRhubarbPhonemeData.MouthCues;
					Character->AudioAnalyser->SetRhubarbPhonemes(RhubarbPhonemes);
					Character->AudioAnalyser->PlayAudioComponent(AudioComponent);
				}
			}
		}
	}
}

void USpeechComponent::CreateSpeechBuuble(FString Text, float FontSize, float Duration)
{
	if (CurrentSpeechBubble) {
		CurrentSpeechBubble->Hide();
	}
	AActor* SpeechBubbleActor = GetOwner();
	CurrentSpeechBubble = AddSpeechBubble(
		FText::FromString(Text),
		FontSize,
		Duration,
		&SpeechBubbleLocation,
		&SpeechBubbleRotation,
		&SpeechBubbleScale,
		SpeechBubbleActor,
		CurrentTargetCharacter,
		&DefaultSpeechBubbleClass
	);
	if (CurrentSpeechBubble && CurrentTargetCharacter)
	{
		 CurrentSpeechBubble->Character = CurrentTargetCharacter;
	}
}


ASpeechBubble* USpeechComponent::AddSpeechBubble(FText Text, float FontSize, float VisibilityDuration, FVector* Location, FRotator* Rotation, FVector* Scale, AActor* Actor, AAdventureCharacter* TargetCharacter, TSubclassOf<ASpeechBubble>* SpeechBubbleClass)
{
	TSubclassOf<ASpeechBubble> FinalSpeechBubbleClass;
	if (SpeechBubbleClass)
	{
		FinalSpeechBubbleClass = *SpeechBubbleClass;
	}
	if (!FinalSpeechBubbleClass)
	{
		FinalSpeechBubbleClass = DefaultSpeechBubbleClass;
	}
	if (FinalSpeechBubbleClass && FinalSpeechBubbleClass.Get())
	{
		UWorld* World = GetWorld();
		if (Character) {
			if (!World) 
			{
				World = Character->GetWorld();
			}
		}
		if (World)
		{
			ASpeechBubble* NewSpeechBubble = World->SpawnActor<ASpeechBubble>(FinalSpeechBubbleClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (NewSpeechBubble)
			{
				NewSpeechBubble->SpeechBubbleText = Text;
				NewSpeechBubble->SpeechBubbleFontSize = FontSize;
				if (VisibilityDuration > 0.0f)
				{
					NewSpeechBubble->VisibilityDuration = VisibilityDuration;
					NewSpeechBubble->HideAfterTime = true;
				}
				if (Actor)
				{
					NewSpeechBubble->AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform);
				}
				if (TargetCharacter) 
				{
					NewSpeechBubble->TargetCharacter = TargetCharacter;
					NewSpeechBubble->TextFacesTarget = true;
				}
				NewSpeechBubble->SetActorRelativeLocation(*Location);
				NewSpeechBubble->SetActorRelativeRotation(*Rotation);
				NewSpeechBubble->SetActorScale3D(*Scale);
				return NewSpeechBubble;
			}
		}
	}
	return nullptr;
}
