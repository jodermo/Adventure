

#pragma once

#include "CoreMinimal.h"
#include "AreaActor.h"
#include "TaskArea.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API ATaskArea : public AAreaActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Task Target Area", meta = (ToolTip = "InteractionActor"))
	ATaskActor* ParentTask;
};
