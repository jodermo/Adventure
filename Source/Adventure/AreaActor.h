#pragma once

#include "CoreMinimal.h"
#include "InteractionActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "AreaActor.generated.h"



UCLASS()
class ADVENTURE_API AAreaActor : public AInteractionActor
{
	GENERATED_BODY()
	
public:	
	AAreaActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Recognition", meta = (ToolTip = "The dimensions of the collision box for this area actor."))
	FVector CollisionExtend = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area Recognition", meta = (ToolTip = "The collision component used for area recognition."))
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area Recognition", meta = (ToolTip = "Whether the player is inside this area."))
	bool IsPlayerInside = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area Recognition", meta = (ToolTip = "List of actors currently inside this area."))
	TArray<AActor*> ActorsInside;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Hide character inside this area."))
	bool HideOnBeginPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Hide character inside this area."))
	bool HideCharacter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Trigger game over when player enters this area."))
	bool CharacterDieOnEnter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Trigger game over when player enters this area."))
	bool GameOverOnEnter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Trigger game over when player enters this area."))
	bool WinGameOnEnter = false;





	UFUNCTION(Category = "Area")
	void InitArea();


	virtual void Show() override;


	virtual void Hide() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area Recognition", meta = (ToolTip = "Whether the player is inside this area."))
	bool IsHidden = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Trigger game over when player enters this area."))
	TSubclassOf<AInteractionActor> OverlapBeginInteractionActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Configuration", meta = (ToolTip = "Trigger game over when player enters this area."))
	TSubclassOf<AInteractionActor> OverlapEndInteractionActorClass;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


public:	
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateCharacters();
};
