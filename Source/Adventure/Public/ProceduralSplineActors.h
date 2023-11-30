#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "ProceduralSplineActors.generated.h"

UENUM(BlueprintType)
enum class EProceduralSplineType : uint8
{
	Line    UMETA(DisplayName = "Line"),
	Disc    UMETA(DisplayName = "Disc")
};

UCLASS()
class ADVENTURE_API AProceduralSplineActors : public AActor
{
	GENERATED_BODY()


public:	
	AProceduralSplineActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	EProceduralSplineType SplineType = EProceduralSplineType::Line;

	EProceduralSplineType SelectedSplineType = EProceduralSplineType::Disc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	int NumSplinePoints = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	int NumObjectsToCreate = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	float DistanceAlongSpline = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	float ObjectDistanceAlongSplineFactor = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralSplineActors")
	class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProceduralSplineActors")
	TArray<AActor*> CreatedActors;

	void InitOrUpdateSplineChanges();
	void SetSplineComponent(class USplineComponent* SplineToFollow);
	void ClearObjects();
	void CreateObjects();
	void CreateSpline();
	void CreateDiscSpline(float Radius, int32 Points);
	void CreateLineSpline(FVector PointA, FVector PointB, int32 Points);
	virtual void UpdateSpline(float DeltaTime);
	virtual void UpdateActors(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
private:

};
