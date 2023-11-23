#include "Building.h"


ABuilding::ABuilding()
{
    RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
    RootComponent = RootMesh;   


    UpdateDoors();
}


void ABuilding::BeginPlay()
{
    Super::BeginPlay();
    UpdateDoors();
}

void ABuilding::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    UpdateDoors();
}

void ABuilding::UpdateDoors()
{
    if (DoorComponents.Num() < DoorMeshes.Num())
    {
        for (int32 i = 0; i < DoorComponents.Num(); i++)
        {
            if (i >= 0 && i >= DoorMeshes.Num())
            {
                DoorComponents[i]->DestroyComponent();
            }
        }
    }

    for (int32 i = 0; i < DoorMeshes.Num(); i++)
    {
        if (i >= 0 && i >= DoorComponents.Num())
        {
            UStaticMeshComponent* DoorComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *FString::Printf(TEXT("Door%d"), i));
            if (DoorComponent)
            {
                DoorComponent->AttachToComponent(RootMesh, FAttachmentTransformRules::KeepRelativeTransform);
                // Set the static mesh for the DoorComponent, assuming DoorMeshes is a valid array.
                UStaticMesh* DoorMesh = DoorMeshes[i];
                if (DoorMesh)
                {
                    DoorComponent->SetStaticMesh(DoorMesh);
                }
            }
        }
    }

    UpdateDoorLocations();
    UpdateDoorRotations();

    for (int32 i = 0; i < DoorComponents.Num(); i++)
    {
        if (i >= 0 && i < DoorIndexIsOpen.Num())
        {
            if (DoorIndexIsOpen[i])
            {
                OpenDoor(i);
            }
            else
            {
                CloseDoor(i);
            }
        }
    }
}

void ABuilding::OpenDoor(int32 DoorIndex)
{
    float DoorRotation = 90.0f;
    if (DoorIndex >= 0 && DoorIndex < OpenedDoorRotationAngles.Num())
    {
        DoorRotation = OpenedDoorRotationAngles[DoorIndex];
    }
    DoorIndexIsOpen[DoorIndex] = true;
    return RotateDoor(DoorIndex, DoorRotation);
}

void ABuilding::CloseDoor(int32 DoorIndex)
{
    float DoorRotation = 90.0f;
    if (DoorIndex >= 0 && DoorIndex < ClosedDoorRotationAngles.Num())
    {
        DoorRotation = ClosedDoorRotationAngles[DoorIndex];
    }
    DoorIndexIsOpen[DoorIndex] = false;
    return RotateDoor(DoorIndex, DoorRotation);
}

void ABuilding::RotateDoor(int32 DoorIndex, float TargetRotation)
{
    FRotator DoorRotation = FRotator(0,0,0);
    if (DoorIndex >= 0 && DoorIndex < DoorRotations.Num())
    {
        DoorRotation = DoorRotations[DoorIndex];
    }
    if (DoorIndex >= 0 && DoorIndex < DoorComponents.Num())
    {
        FQuat TargetQuat = (DoorRotation + FRotator(0, TargetRotation, 0)).Quaternion();
        FQuat CurrentQuat = DoorComponents[DoorIndex]->GetComponentRotation().Quaternion();
        FQuat NewQuat = FQuat::Slerp(CurrentQuat, TargetQuat, 0.1f); // Adjust the interpolation speed as needed
        DoorComponents[DoorIndex]->SetWorldRotation(NewQuat.Rotator());
    }
}

void ABuilding::UpdateDoorLocations()
{

    for (int32 i = 0; i < DoorComponents.Num(); i++)
    {
        FVector DoorLocation = FVector(0, 0, 0);
        if (i >= 0 && i < DoorLocations.Num())
        {
            DoorLocation = DoorLocations[i];
        }
        DoorComponents[i]->SetRelativeLocation(DoorLocation);
    }
}

void ABuilding::UpdateDoorRotations()
{
    for (int32 i = 0; i < DoorComponents.Num(); i++)
    {
        FRotator DoorRotation = FRotator(0, 0, 0);
        if (i >= 0 && i < DoorRotations.Num())
        {
            DoorRotation = DoorRotations[i];
        }
        DoorComponents[i]->SetRelativeRotation(DoorRotation);
    }
}

void ABuilding::OpenAllDoors()
{
    for (int32 i = 0; i < DoorComponents.Num(); i++)
    {
        OpenDoor(i);
    }
}

void ABuilding::CloseAllDoors()
{
    for (int32 i = 0; i < DoorComponents.Num(); i++)
    {
        CloseDoor(i);
    }
}