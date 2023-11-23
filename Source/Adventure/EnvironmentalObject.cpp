#include "EnvironmentalObject.h"
#include "AdventureGameModeBase.h"


AEnvironmentalObject::AEnvironmentalObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnvironmentalObject::BeginPlay()
{
	Super::BeginPlay();
}

void AEnvironmentalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnvironmentalObject::InitObject()
{
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
	if (GameMode)
	{
		GameMode->EnvironmentalObjects.Add(this);
	}
	RootPrimitive = Cast<UPrimitiveComponent>(RootComponent);
}

void AEnvironmentalObject::InteractWithObject_Implementation(AActor* InteractingActor)
{
	// Default interaction behavior for the environmental object.
	// You can override this function in child classes to define specific interactions.
}

void AEnvironmentalObject::ReceiveDamage(float DamageAmount)
{
	if (IsDestructible)
	{
		Health -= DamageAmount;
		if (Health <= 0.0f)
		{
			// Object has been destroyed, perform destruction logic here.
			OnDestroyed();
		}
	}
}

void AEnvironmentalObject::OnDestroyed_Implementation()
{
	// Default destroed behavior for the environmental object.
	// You can override this function in child classes to define specific interactions.
}
