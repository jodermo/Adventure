#include "SpeechBubble.h"
#include "GameCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "AdventureCharacter.h"
#include "Camera/CameraComponent.h"

ASpeechBubble::ASpeechBubble()
{
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = RootMesh;

	SpeechBubbleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpeechBubbleMesh"));
	SpeechBubbleMesh->SetupAttachment(RootMesh);
	SpeechBubbleMesh->SetRelativeLocation(SpeechBubblePosition);
	SpeechBubbleMesh->SetRelativeRotation(SpeechBubbleRotation);

	SpeechBubbleWidgetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeechBubbleWidgetMesh"));
	SpeechBubbleWidgetMesh->SetupAttachment(SpeechBubbleMesh);


	SpeechBubbleFrontWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubbleFrontWidget"));
	SpeechBubbleFrontWidget->SetupAttachment(SpeechBubbleWidgetMesh);
	SpeechBubbleFrontWidget->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	SpeechBubbleBackWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubbleBackWidget"));
	SpeechBubbleBackWidget->SetupAttachment(SpeechBubbleWidgetMesh);
	SpeechBubbleBackWidget->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

}


void ASpeechBubble::Log(FString LogMessage) {
	GEngine->AddOnScreenDebugMessage(LogKey, LogTime, LogColor, LogMessage);
}

void ASpeechBubble::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SpeechBubbleMesh->SetRelativeLocation(SpeechBubblePosition);
	SpeechBubbleMesh->SetRelativeRotation(SpeechBubbleRotation);
	SetText(SpeechBubbleText);
}

void ASpeechBubble::BeginPlay()
{
	Super::BeginPlay();
	InitWidget();
	AnimInstance = SpeechBubbleMesh->GetAnimInstance();

	if (VisibilityDuration > 0.0f) {
		HideAfterTime = true;
	}

	if (AnimInstance && FadeInAnimation) {

		StartAnimation(FadeInAnimation, FadeInAnimationRate, [this]()
			{
				IsReady = true;
			});
	}
	else {
		IsReady = true;
	}

}

void ASpeechBubble::InitWidget() 
{
	if (SpeechBubbleTextWidgetClass && SpeechBubbleTextWidgetClass.Get())
	{
		if (SpeechBubbleFrontWidget)
		{
			SpeechBubbleFrontTextWidget = CreateWidget<USpeechBubbleWidget>(GetWorld(), SpeechBubbleTextWidgetClass);
			SpeechBubbleFrontWidget->SetWidget(SpeechBubbleFrontTextWidget);
		}
		if (SpeechBubbleBackWidget)
		{
			SpeechBubbleBackTextWidget = CreateWidget<USpeechBubbleWidget>(GetWorld(), SpeechBubbleTextWidgetClass);
			SpeechBubbleBackWidget->SetWidget(SpeechBubbleBackTextWidget);
		}
	}

	UpdateWidget(0.0f);
}


void ASpeechBubble::UpdateWidget(float DeltaTime)
{

	SetText(SpeechBubbleText);

	SpeechBubbleMesh->SetRelativeLocation(SpeechBubblePosition);
	SpeechBubbleMesh->SetRelativeRotation(SpeechBubbleRotation);

	if (SpeechBubbleFrontTextWidget)
	{
		SpeechBubbleFrontTextWidget->UpdateText(SpeechBubbleText);
		SpeechBubbleFrontTextWidget->UpdateFont(SpeechBubbleFont);
		SpeechBubbleFrontTextWidget->UpdateFontSize(SpeechBubbleFontSize);
		SpeechBubbleFrontTextWidget->UpdateTextColor(SpeechBubbleTextColor);
	}
	if (SpeechBubbleBackTextWidget)
	{
		SpeechBubbleBackTextWidget->UpdateText(SpeechBubbleText);
		SpeechBubbleBackTextWidget->UpdateFont(SpeechBubbleFont);
		SpeechBubbleBackTextWidget->UpdateFontSize(SpeechBubbleFontSize);
		SpeechBubbleBackTextWidget->UpdateTextColor(SpeechBubbleTextColor);
	}

	if (TextFacesTarget && TargetCharacter)
	{
		FVector TargetLocation = FVector::ZeroVector;

		// Check if the target character has a camera component
		if (TargetCharacter->CurrentCameraComponent)
		{
			// Use the camera's world position as the target location
			TargetLocation = TargetCharacter->CurrentCameraComponent->GetComponentLocation();
		}
		else
		{
			// Use the target character's location if there's no camera component
			TargetLocation = TargetCharacter->GetActorLocation();
		}

		// Calculate the rotation to make the speech bubble face the target location
		FRotator FaceCharacterRotation = (TargetLocation - GetActorLocation()).Rotation();

		// Calculate the rotation needed to align the widget with the camera
		FRotator WidgetRotation = FaceCharacterRotation + FRotator(-45.0f, 90.0f, 0.0f);

		// Set the world rotation of the SpeechBubbleWidgetMesh
		SpeechBubbleWidgetMesh->SetWorldRotation(WidgetRotation);
	}





	if (HideAfterTime) {

		if (VisibilityDuration > 0.0f) {
			VisibilityDuration -= DeltaTime;
		}
		if (VisibilityDuration <= 0.0f) {
			VisibilityDuration = 0.0f;
			Hide();
		}
	}
}


void ASpeechBubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateWidget(DeltaTime);
}

void ASpeechBubble::SetText(FText Text)
{
	SpeechBubbleText = Text;
}

void ASpeechBubble::Hide()
{
	if (Character && Character->SpeechBubble == this) {
		Character->SpeechBubble = nullptr;
	}
	if (Vehicle && Vehicle->SpeechBubble == this) {
		Vehicle->SpeechBubble = nullptr;
	}
	if (AnimInstance && FadeOutAnimation)
	{
		StartAnimation(FadeOutAnimation, FadeOutAnimationRate,[this]()
			{
				Destroy();
			}
		);
	}
	else
	{
		Destroy();
	}
}



void ASpeechBubble::StartAnimation(UAnimSequence* AnimSequence, float AnimationRate, TFunction<void()> OnAnimationEnded)
{
	if (!AnimInstance)
	{
		AnimInstance = SpeechBubbleMesh->GetAnimInstance();
		if (AnimInstance)
		{
			AnimMontage = AnimInstance->GetCurrentActiveMontage();
		}
	}
	if (AnimSequence && AnimInstance && AnimMontage)
	{
		AnimInstance->Montage_SetPlayRate(AnimMontage, AnimationRate);
		AnimInstance->Montage_Play(AnimMontage);
		AnimInstance->PlaySlotAnimationAsDynamicMontage(AnimSequence, FName("DefaultSlot"), 0.f, 0.f, AnimationRate);
		FTimerHandle TimerHandle;
		float AnimationDuration = AnimSequence->GetPlayLength();
		GetWorldTimerManager().SetTimer(TimerHandle, [&]() {
			OnAnimationEnded();
			}, AnimationDuration, false);
	}
}


