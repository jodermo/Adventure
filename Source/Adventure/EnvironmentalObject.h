#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentalObject.generated.h"

class AAdventureGameModeBase;

UCLASS()
class ADVENTURE_API AEnvironmentalObject : public AActor
{
	GENERATED_BODY()

public:
	AEnvironmentalObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Environmental Object", meta = (ToolTip = "GameMode."))
	AAdventureGameModeBase* GameMode;

	virtual void InitObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Environmental Object")
	bool IsDestructible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Environmental Object")
	float Health = 100.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Environmental Object")
	float VehicleWheelResistance = 0.5f;


	UFUNCTION(BlueprintNativeEvent, Category = "Game Environmental Object")
	void InteractWithObject(AActor* InteractingActor);
	virtual void InteractWithObject_Implementation(AActor* InteractingActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Game Environmental Object")
	void OnDestroyed();
	virtual void OnDestroyed_Implementation();



protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Environmental Object")
	void ReceiveDamage(float DamageAmount);

private:
	UPrimitiveComponent* RootPrimitive;
};
