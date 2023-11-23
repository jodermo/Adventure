

#include "VehicleInteractionrComponent.h"
#include "AdventureCharacter.h"
#include "ItemActor.h"
#include "EnvironmentalObject.h"
#include "Components/SceneComponent.h"

UVehicleInteractionrComponent::UVehicleInteractionrComponent()
{
    Logger = CreateDefaultSubobject<ULogging>(TEXT("Logger"));
    PrimaryComponentTick.bCanEverTick = true;
    InitComponent();
}

void UVehicleInteractionrComponent::OnConstruction(const FTransform& Transform)
{
    InitComponent();
}

void UVehicleInteractionrComponent::BeginPlay()
{
    Super::BeginPlay();
    InitComponent();
}

void UVehicleInteractionrComponent::InitComponent()
{

    OwnerActor = GetOwner();

    if (OwnerActor)
    {
        Vehicle = Cast<AVehicle>(OwnerActor);
    }

}

void UVehicleInteractionrComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UVehicleInteractionrComponent::DoObjectInteraction(AEnvironmentalObject* EnvironmentalObject, float DeltaTime)
{
    if (Vehicle && EnvironmentalObject)
    {
        FVector VehicleVelocity = Vehicle->RootPrimitive->GetPhysicsLinearVelocity();
        FVector ResistanceDirection = -VehicleVelocity.GetSafeNormal();
        float WheelResistanceMagnitude = VehicleVelocity.Size() * EnvironmentalObject->VehicleWheelResistance;
        FVector WheelResistance = ResistanceDirection * WheelResistanceMagnitude;
        Vehicle->RootPrimitive->AddForce(WheelResistance);
    }
}

void UVehicleInteractionrComponent::DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{
    InitComponent();
    if (GivePoints)
    {
        if (GivePointsOnlyOnce && !AwardedPoints)
        {
            TargetCharacter->AddPoints(PointsToGive);
            if (RemovePointsAfterGiven)
            {
                PointsToGive = 0;
            }
            AwardedPoints = true;
        }
        else if (!GivePointsOnlyOnce)
        {
            TargetCharacter->AddPoints(PointsToGive);
            AwardedPoints = true;
        }
    }
    if (Vehicle)
    {
        if (EnterVehicle) 
        {
            Vehicle->OnEnterVehicle(TargetCharacter);
        }
        if (TriggerInteraction) 
        {
            DoCharacterActorInteraction(TargetCharacter, DeltaTime);
        }
    }
}

void UVehicleInteractionrComponent::DoCharacterActorInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{
    if (InteractionActorClasses.Num() > 0 && TriggerInteractionIndex == NextInteractionIndex)
    {
        CurrentInteractionIndex = NextInteractionIndex;
        if (CurrentInteractionIndex < InteractionActorClasses.Num())
        {
            TSubclassOf<AInteractionActor> InteractionActorClass = InteractionActorClasses[CurrentInteractionIndex];
            if (InteractionActorClass)
            {

                AInteractionActor* InteractionActor = GetWorld()->SpawnActor<AInteractionActor>(InteractionActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
                InteractionActor->Vehicle = Vehicle;
                InteractionActor->TargetCharacter = TargetCharacter;
                if (InteractionActor)
                {
                    TriggerInteractionActor(TargetCharacter, InteractionActor, DeltaTime);
                }

                NextInteractionIndex++;
            }
        }
    }
}

void UVehicleInteractionrComponent::TriggerInteractionActor(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor, float DeltaTime)
{

    if (InteractionActor)
    {
        if (InteractionActor->SpeakToActor)
        {
            // float InteractionActor->PointsToGive
        }
        if (InteractionActor->AskQuestion)
        {
            // float InteractionActor->PointsToGive
           //  TArray<TSubclassOf<AAnswerActor>> InteractionActor->InteractionAnswerClasses
        }
        if (InteractionActor->TriggerTasks)
        {
            InteractionActor->TriggerNextTask();
        }
       
        if (InteractionActor->GivePoints)
        {
            if (InteractionActor->GivePointsOnlyOnce && !InteractionActor->AwardedPoints)
            {
                TargetCharacter->AddPoints(InteractionActor->PointsToGive);

                InteractionActor->AwardedPoints = true;
            }
            else if (!InteractionActor->GivePointsOnlyOnce)
            {
                TargetCharacter->AddPoints(InteractionActor->PointsToGive);
                InteractionActor->AwardedPoints = true;
            }
        }
        if (InteractionActor->GiveItems)
        {
            for (TSubclassOf<AItemActor> InteractionItemClass : InteractionActor->InteractionItemClasses)
            {
                AItemActor* InteractionItem = GetWorld()->SpawnActor<AItemActor>(InteractionItemClass, FVector::ZeroVector, FRotator::ZeroRotator);

                TargetCharacter->PickupItem(InteractionItem, TargetCharacter->ItemsSlot);
            }

        }
        if (InteractionActor->GiveActor)
        {

            TargetCharacter->AddInteractionActor(InteractionActor);
        }
        OnCharacterActorInteraction(TargetCharacter, InteractionActor, DeltaTime);
    }

}

void UVehicleInteractionrComponent::OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{


}

void UVehicleInteractionrComponent::OnCharacterActorInteraction(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor, float DeltaTime)
{


}

