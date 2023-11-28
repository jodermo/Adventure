
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "DraggableActor.generated.h"

class AAdventureGameModeBase;

UCLASS()
class ADVENTURE_API ADraggableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADraggableActor();

	AAdventureGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	UStaticMeshComponent* RootMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	bool Draggable = false;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void InitDraggableActor();

};
