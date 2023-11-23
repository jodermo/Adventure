#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"


UCLASS(Blueprintable)
class ADVENTURE_API ABuilding : public AActor
{
    GENERATED_BODY()

public:
    ABuilding();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building", meta = (ToolTip = "The static mesh component of the building"))
    UStaticMeshComponent* RootMesh;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<UStaticMeshComponent*> DoorComponents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<FVector> DoorLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<FRotator> DoorRotations;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<UStaticMesh*> DoorMeshes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<float> OpenedDoorRotationAngles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<float> ClosedDoorRotationAngles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors", meta = (ToolTip = "Door Components"))
    TArray<bool> DoorIndexIsOpen;

    UFUNCTION(BlueprintCallable, Category = "Doors", meta = (ToolTip = "Open Door"))
    void OpenDoor(int32 DoorIndex);

    UFUNCTION(BlueprintCallable, Category = "Doors", meta = (ToolTip = "Open Door"))
    void CloseDoor(int32 DoorIndex);

    UFUNCTION(BlueprintCallable, Category = "Doors", meta = (ToolTip = "Open Door"))
    void RotateDoor(int32 DoorIndex, float TargetRotation);

    UFUNCTION(BlueprintCallable, Category = "Doors", meta = (ToolTip = "Open Door"))
    void OpenAllDoors();

    UFUNCTION(BlueprintCallable, Category = "Doors", meta = (ToolTip = "Open Door"))
    void CloseAllDoors();

    void UpdateDoors();

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

private:

    void UpdateDoorLocations();
    void UpdateDoorRotations();
};
