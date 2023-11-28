
#include "DraggableActor.h"
#include "../AdventureGameModeBase.h"

ADraggableActor::ADraggableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = RootMesh;
}

void ADraggableActor::BeginPlay()
{
	Super::BeginPlay();
	InitDraggableActor();
}
void ADraggableActor::InitDraggableActor()
{
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
	if (Draggable && GameMode && !GameMode->DraggableActors.Contains(this))
	{
		GameMode->DraggableActors.Add(this);
	}
}
void ADraggableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

