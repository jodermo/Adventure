
#pragma once

#include "CoreMinimal.h"
#include "AdventureGameModeBase.h"
#include "ItemActor.h"
#include "Tool.generated.h"

class AAdventureCharacter;


UCLASS(Blueprintable)
class ADVENTURE_API ATool : public AItemActor
{
	GENERATED_BODY()

public:

	ATool();

	AAdventureGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Charge"))
	float Charge = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Consumption"))
	float Consumption = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Use tool on impact"))
	bool UseOnImpact = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Tool", meta = (ToolTip = "Is tool using tool"))
	bool IsUsing = false;

	UFUNCTION(BlueprintCallable, Category = "Game Tool", meta = (ToolTip = "Start use tool"))
	virtual void StartUse();

	UFUNCTION(BlueprintCallable, Category = "Game Tool", meta = (ToolTip = "Stop use tool"))
	virtual void StopUse();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Tool", meta = (ToolTip = "Current apply actor"))
	AActor* ApplyActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Tool", meta = (ToolTip = "Is applying"))
	bool IsApplying = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Apply on impact"))
	bool ApplyOnImpact = false;

	UFUNCTION(BlueprintCallable, Category = "Game Tool", meta = (ToolTip = "Start apply tool an actor"))
	virtual void StartApply(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Game Tool", meta = (ToolTip = "Stop apply tool an actor"))
	virtual void StopApply();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Use tool on impact"))
	bool DropIfEmpty = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Tool", meta = (ToolTip = "Use tool on impact"))
	bool DetroyIfEmpty = false;


	virtual void Drop() override;

protected:

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void InitTool();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateUse(float DeltaTime);
	virtual void UpdateApply(float DeltaTime);
	virtual void UpdateCharge(float DeltaTime);
};
