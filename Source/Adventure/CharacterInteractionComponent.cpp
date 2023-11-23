#include "CharacterInteractionComponent.h"
#include "AdventureCharacter.h"
#include "ItemActor.h"
#include "Components/SceneComponent.h"

UCharacterInteractionComponent::UCharacterInteractionComponent()
{
    Logger = CreateDefaultSubobject<ULogging>(TEXT("Logger"));
	PrimaryComponentTick.bCanEverTick = true;
    InitComponent();
}

void UCharacterInteractionComponent::OnConstruction(const FTransform& Transform)
{
    InitComponent();
}

void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
    InitComponent();
}

void UCharacterInteractionComponent::InitComponent()
{
    OwnerActor = GetOwner();
    if (OwnerActor)
    {
        Character = Cast<AAdventureCharacter>(OwnerActor);
    }
}

void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterInteractionComponent::DoCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{
    InitComponent();
    if (MakeDamage)
    {
        if (MakeDamageOnlyOnce && !DidDamage)
        {
            Character->Attack(TargetCharacter, DamageMultiplicator, 1.0f);
        }
        else if (!MakeDamageOnlyOnce)
        {
            Character->Attack(TargetCharacter, DamageMultiplicator, DeltaTime);
        }
    }
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
    if (Character)
    {
        DoCharacterActorInteraction(TargetCharacter, DeltaTime);
    }
}

void UCharacterInteractionComponent::DoCharacterActorInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
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
                if (InteractionActor)
                {
                    InteractionActor->SetCharacter(Character);
                    Character->TriggerInteractionActor(TargetCharacter, InteractionActor);
                }
                NextInteractionIndex++;
            }
        }
    }
}

void UCharacterInteractionComponent::OnCharacterInteraction(AAdventureCharacter* TargetCharacter, float DeltaTime)
{


}

void UCharacterInteractionComponent::OnCharacterActorInteraction(AAdventureCharacter* TargetCharacter, AInteractionActor* InteractionActor, float DeltaTime)
{
    if (Character) {
        Character->CurrentInteractionActor = InteractionActor;
        //TargetCharacter->CurrentInteractionActor = InteractionActor;
    }
}