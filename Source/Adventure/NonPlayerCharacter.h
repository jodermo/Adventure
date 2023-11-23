
#pragma once

#include "CoreMinimal.h"
#include "AdventureCharacter.h"
#include "CustomProceduralMeshComponent.h"
#include "NavigationSystem.h" 
#include "NavigationPath.h"
#include "NonPlayerCharacter.generated.h"


UCLASS()
class ADVENTURE_API ANonPlayerCharacter : public AAdventureCharacter
{
	GENERATED_BODY()
	
public:
	ANonPlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Static mesh component representing the field of view"))
	UStaticMeshComponent* FieldOfViewMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Procedural mesh component representing the field of view"))
	UCustomProceduralMeshComponent* ProceduralFieldOfViewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Material for the field of view"))
	UMaterialInterface* FieldOfViewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Material for the field of view"))
	UMaterialInterface* FieldOfViewRecognitionMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Offset for the field of view mesh"))
	FVector FieldOfViewOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Distance at which the NPC starts sprinting"))
	float SprintingDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Maximum distance at which the NPC recognizes characters"))
	float MaxRecognitionDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC can detect characters"))
	bool CanDetectCharacters = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Field of view angle for NPC detection"))
	bool UseFieldOfViewMesh = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Field of view angle for NPC detection"))
	float FieldOfViewAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC should look around"))
	bool LookAround = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Speed of NPC's look around movement"))
	float LookAroundSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Maximum distance for NPC's look around"))
	float MaxLookAroundDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC should move around"))
	bool MoveAround = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC can detect characters"))
	bool StepBackIfToClose = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Radius within which the NPC moves around"))
	float MoveAroundRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Maximum distance to target location"))
	float MaxTargetDistance = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Distance for stepping back"))
	float StepBackDistance = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC is stepping back"))
	float SteppingBack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Amount of step back movement"))
	float StepBackAmount = 200.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Value indicating step back progress"))
	float StepBackValue = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Speed of step back movement"))
	float StepBackSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game NPC", meta = (ToolTip = "Duration for looking around"))
	float LookAroundDuration = 3.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC is looking at a character"))
	bool IsLookingAtCharacter = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Reference to the target character"))
	AAdventureCharacter* TargetCharacter = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating preference for player character as the target"))
	bool PreferPlayerCharacter = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the target is within sprinting distance"))
	bool TargetIsWithinSprintDistance = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Distance to target character"))
	float TargetDistance = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Angle to target character"))
	float TargetAngle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Location of the target character"))
	FVector TargetLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Direction towards the target character"))
	FVector TargetDirection = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Distance to the target location"))
	float DistanceToTarget = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC is currently looking around"))
	bool IsLookingAround = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Flag indicating if the NPC is currently moving around"))
	bool IsMovingAround = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Current movement speed of the NPC"))
	float CurrentMovementSpeed = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Set the current movement speed of the NPC"))
	void SetCurrentMovementSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Show the field of view mesh"))
	void ShowFieldOfViewMesh();

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Hide the field of view mesh"))
	void HideFieldOfViewMesh();

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Move the NPC to a specific location"))
	void MoveToLocation(FVector NewTargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Generate a random location within a given radius"))
	FVector GenerateRandomLocationInRadius(float MoveRadius);

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Move the NPC to a random location within a given radius"))
	void MoveToRandomLocationInRadius(float MoveRadius);

	void RetryMoveToRandomLocation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game NPC", meta = (ToolTip = "Time to retry when failed to find a valid location."))
	float RetryMoveToRandomLocationDelay = 2.0f;

	UFUNCTION(BlueprintCallable, Category = "Game NPC", meta = (ToolTip = "Check if a character is within the NPC's field of view"))
	bool IsCharacterInViewField(AAdventureCharacter* Character, float CharacterRecognitionDistance);

	virtual bool CanAttackCharacter(AAdventureCharacter* Character) override;


	virtual void InitCharacter() override;


	virtual void IgnoreCharacter(AAdventureCharacter* CharacterToIgnore) override;

	virtual AVehicle* GetClosestVehicle() override;

	virtual void Die() override;

private:
	TArray<FVector> PathPoints;

	void UpdateLookAround(float DeltaSeconds);
	float CalculateRecognitionDistance(AAdventureCharacter* Character);
	void UpdateMoveToTarget(float DeltaSeconds);
	void UpdateMoveToCharacter(float DeltaSeconds);
	void UpdateFieldOfViewMesh(float DeltaSeconds);
	bool IsBestTarget(AAdventureCharacter* Character);
	void ClearTarget();


	FRotator TargetLookDirection;
	float LookAroundTime;
	void GenerateProceduralFieldOfViewMesh(float ConeAngle, float ConeHeight, int32 NumSides, float ConeRadius);

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
