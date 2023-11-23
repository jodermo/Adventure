
#include "TaskActor.h"
#include "AdventureCharacter.h"
#include "EngineUtils.h"

ATaskActor::ATaskActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATaskActor::BeginPlay()
{
	Super::BeginPlay();
	FindTargetAreas();
}

void ATaskActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ATaskArea*> ATaskActor::FindTargetAreas()
{
	TargetAreas.Empty();
    if (TargetAreaClass && TargetAreaClass.Get())
    {
        for (TActorIterator<ATaskArea> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            ATaskArea* FoundTaskArea = *ActorItr;
            TargetAreas.Add(FoundTaskArea);
			if (ShowAreasOnTaskInteraction)
			{
				FoundTaskArea->Hide();
			}
        }
    }
    return TargetAreas;
}

void ATaskActor::TriggerCharacterTask(AAdventureCharacter* ForCharacter)
{
	TargetCharacter = ForCharacter;
	TargetCharacter->AddTaskActor(this);
	for (ATaskArea* TargetArea : TargetAreas)
	{
		TargetCharacter->AddTargetArea(this, TargetArea);
		if (ShowAreasOnTaskInteraction)
		{
			TargetArea->Show();
		}
	}
}