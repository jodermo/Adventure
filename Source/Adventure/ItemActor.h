#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging.h"
#include "ItemCombination.h"
#include "SpeechBubble.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DraggableActor.h"
#include "ItemActor.generated.h"

class AInteractionActor;
class AAdventureCharacter;
class AAdventureGameModeBase;

UCLASS()
class ADVENTURE_API AItemActor : public ADraggableActor
{
	GENERATED_BODY()

public:
	AItemActor();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging")
	ULogging* Logger;


protected:
	virtual void BeginPlay() override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Actor", meta = (ToolTip = "Mesh"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	UNiagaraSystem* PickUpParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	FVector PickUpParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	UNiagaraSystem* PickUpCharacterParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	FVector PickUpCharacterParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	UNiagaraSystem* UseParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	FVector UseParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	UAudioComponent* PickUpSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Effects")
	UAudioComponent* UseSoundComponent;


	UFUNCTION(BlueprintCallable,  Category = "Item Effects")
	virtual void TriggerPickUpEffects(AAdventureCharacter* TargetCharacter);


	UFUNCTION(BlueprintCallable, Category = "Item Effects")
	virtual void TriggerUseEffects();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Logging")
	AAdventureCharacter* InteractionCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Logging")
	AAdventureCharacter* Character;

	UFUNCTION(BlueprintCallable, Category = "Interaction Actor", meta = (ToolTip = "Select task based on given index"))
	virtual void SetCharacter(AAdventureCharacter* ItemCharacter);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Logging")
	int32 LogKey = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Logging")
	FColor LogColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Logging")
	float LogTime = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "Item Logging")
	void Log(FString LogMessage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	FString ItemAlias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Speech Bubble Class"))
	TSubclassOf<ASpeechBubble> SpeechBubbleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Speech bubble of the item"))
	ASpeechBubble* SpeechBubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool Selected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool Collectable = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Make character unrecognizable inside this area."))
	bool MakeCharacterUnrecognisable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Make character recognizable inside this area."))
	bool MakeCharacterRecognisable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool DetroyAfterUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool Stackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	int Stack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool OpenInventarOnPickUp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor")
	bool CharacterDieOnPickUp = false;

	UFUNCTION(BlueprintCallable, Category = "Item Actor")
	virtual void PickedUpByCharacter(AAdventureCharacter* TargetCharacter, bool AsDefault, FName SlotName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Character")
	void OnPickedUpByCharacter(AAdventureCharacter* TargetCharacter, bool AsDefault, FName SlotName);


	UFUNCTION(BlueprintCallable, Category = "Item Actor")
	virtual void Drop();

	UFUNCTION(BlueprintCallable, Category = "Item Actor")
	virtual void Use();

	UFUNCTION(BlueprintCallable, Category = "Item Actor")
	virtual void Show();

	UFUNCTION(BlueprintCallable, Category = "Item Actor")
	virtual void Hide();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Trigger interaction actor when answer gets triggered."))
	bool TriggerInteraction = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Trigger interaction actor when answer gets triggered."))
	bool TriggerInteractionOnlyOnce = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor", meta = (ToolTip = "Class of the next interaction actor triggered by selecting this answer."))
	TSubclassOf<AInteractionActor> InteractionActorClass;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Collected items for combination"))
	TArray<UItemCombination*> ItemCombinations;

	UFUNCTION(BlueprintCallable, Category = "Item Actor", meta = (ToolTip = "ShowSpeechBuuble"))
	void ShowSpeechBuuble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Item Actor", meta = (ToolTip = "GetCharacterItemSlot"))
	FName GetCharacterItemSlot(AAdventureCharacter* TargetCharacter, bool FromInventar);


	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
