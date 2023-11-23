
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "SpeechBubbleWidget.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Styling/SlateTypes.h"
#include "Engine/Font.h"
#include "Math/Color.h"
#include "SpeechBubble.generated.h"

class AAdventureCharacter;
class AVehicle;
class AItemActor;

UCLASS(Blueprintable)
class ADVENTURE_API ASpeechBubble : public AActor
{
	GENERATED_BODY()

public:

	ASpeechBubble();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Character of the speech bubble"))
	AAdventureCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Vehicle of the speech bubble"))
	AVehicle* Vehicle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Item of the speech bubble"))
	AItemActor* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Key for character logging"))
	int32 LogKey = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Color for character logging messages"))
	FColor LogColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logging", meta = (ToolTip = "Time duration for which character logging messages will be displayed"))
	float LogTime = 5.0f;


	UFUNCTION(BlueprintCallable, Category = "Game Mode", meta = (ToolTip = "Log a message related to the character"))
	void Log(FString LogMessage);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "User Widget class for the speech bubble text"))
	TSubclassOf<USpeechBubbleWidget> SpeechBubbleTextWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	bool TextFacesTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	bool HideAfterTime = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	float VisibilityDuration = 0.0f;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	UTexture2D* SpeechBubbleIcon;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Image for the speech bubble"))
	UTexture2D* SpeechBubbleImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Text in the speech bubble"))
	FText SpeechBubbleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	float SpeechBubbleFontSize = 60.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Text Color"))
	FLinearColor SpeechBubbleTextColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "SpeechBubbleFont"))
	UFont* SpeechBubbleFont;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Description of the speech bubble"))
	FText SpeechBubbleDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "The static mesh component of the speech bubble"))
	UStaticMeshComponent* RootMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "The skeletal mesh component of the speech bubble"))
	USkeletalMeshComponent* SpeechBubbleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "The static mesh component of the speech bubble"))
	FVector SpeechBubblePosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "The static mesh component of the speech bubble"))
	FRotator SpeechBubbleRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "The static mesh component of the speech bubble"))
	UStaticMeshComponent* SpeechBubbleWidgetMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game SpeechBubble")
	UWidgetComponent* SpeechBubbleFrontWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game SpeechBubble")
	UWidgetComponent* SpeechBubbleBackWidget;



	USpeechBubbleWidget* SpeechBubbleFrontTextWidget;
	USpeechBubbleWidget* SpeechBubbleBackTextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Icon for the speech bubble"))
	AAdventureCharacter* TargetCharacter;

	UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "SetText"))
	void SetText(FText Text);

	UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "Hide"))
	void Hide();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "FadeInAnimation"))
	class UAnimSequence* FadeInAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "FadeInAnimationRate"))
	float FadeInAnimationRate = 1.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "FadeOutAnimation"))
	class UAnimSequence* FadeOutAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ToolTip = "FadeOutAnimationRate"))
	float FadeOutAnimationRate = 1.0f;

	UAnimInstance* AnimInstance;
	UAnimMontage* AnimMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game SpeechBubble", meta = (ToolTip = "IsReady"))
	bool IsReady = false;


protected:

	virtual void OnConstruction(const FTransform& Transform) override;


	virtual void BeginPlay() override;

	virtual void InitWidget();

	virtual void UpdateWidget(float DeltaTime);

	virtual void StartAnimation(UAnimSequence* AnimSequence, float AnimationRate, TFunction<void()> OnAnimationEnded);

public:
	virtual void Tick(float DeltaTime) override;
};