#include "AreaActor.h"
#include "AdventureCharacter.h"
#include "InteractionActor.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AAreaActor::AAreaActor()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAreaActor::OnOverlapBegin);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAreaActor::OnOverlapEnd);
    CollisionComponent->SetBoxExtent(CollisionExtend);
}

void AAreaActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    InitArea();
}

void AAreaActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    InitArea();
}

void AAreaActor::BeginPlay()
{
    Super::BeginPlay();
    InitArea();
    if(HideOnBeginPlay)
    {
        Hide();
    }
}

void AAreaActor::InitArea()
{
    CollisionComponent->SetBoxExtent(CollisionExtend);
    FVector NewRelativeLocation = FVector(0.0f, 0.0f, CollisionExtend.Z * 0.5f);
}

void AAreaActor::Show()
{
    IsHidden = false;
    RootComponent->SetVisibility(true);
    CollisionComponent->SetVisibility(true);
    SetActorHiddenInGame(false);
}

void AAreaActor::Hide()
{
    IsHidden = true;
    RootComponent->SetVisibility(false);
    CollisionComponent->SetVisibility(false);
    SetActorHiddenInGame(true);
}

void AAreaActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAreaActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsHidden) {
        ActorsInside.Add(OtherActor);
        if (OtherActor && OtherActor->IsA(AAdventureCharacter::StaticClass()))
        {
            IsPlayerInside = true;
            AAdventureCharacter* CharacterInside = Cast<AAdventureCharacter>(OtherActor);
            if (CharacterInside)
            {
                CharacterInside->OnAreaOverlapBegin(this);
                if (OverlapBeginInteractionActorClass) {
                    TriggerInteractionClass(nullptr,  CharacterInside, OverlapBeginInteractionActorClass);
                }
            }
        }
    }
}

void AAreaActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ActorsInside.Remove(OtherActor);
    if (OtherActor && OtherActor->IsA(AAdventureCharacter::StaticClass()))
    {
        IsPlayerInside = false;
        AAdventureCharacter* CharacterInside = Cast<AAdventureCharacter>(OtherActor);
        if (CharacterInside)
        {
            CharacterInside->OnAreaOverlapEnd(this);

            if (OverlapEndInteractionActorClass) {
               TriggerInteractionClass(nullptr, CharacterInside, OverlapEndInteractionActorClass);
            }
        }
    }
}

void AAreaActor::UpdateCharacters()
{
    for (AActor* Actor : ActorsInside)
    {
        if (Actor)
        {
            // For example, you can call a function on the character
            // to perform some action based on being inside the area
           // Character->AreaUpdate(this);
        }
    }
}