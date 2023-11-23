
#include "ItemCombination.h"
#include "ItemActor.h"


UItemCombination::UItemCombination()
{

	PrimaryComponentTick.bCanEverTick = true;

}



void UItemCombination::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();


	
}
void UItemCombination::InitComponent()
{

	OwnerActor = GetOwner();

	if (OwnerActor)
	{
		BaseItem = Cast<AItemActor>(OwnerActor);
		BaseItem->ItemCombinations.Add(this);
	}

}

void UItemCombination::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UItemCombination::AddItem(AItemActor* CombinationItem)
{
	if (CombinationItem)
	{
		AvailableItems.Add(CombinationItem);
        OnItemAdded(CombinationItem);
	}
}

void UItemCombination::RemoveItem(AItemActor* CombinationItem)
{
	if (CombinationItem)
	{
		AvailableItems.Remove(CombinationItem);
        OnItemRemoved(CombinationItem);
	}
}


void UItemCombination::CombineItems()
{
    CombinationResultInfo = nullptr;
    WrongItems.Empty(); // Clear the WrongItems array

    if (BaseItem)
    {
        // Check if the BaseItem and combination items match the required combination
        bool bCanCombine = true;
        for (const TSubclassOf<AItemActor>& CombinationItemClass : CombinationItemClasses)
        {
            bool bContainsCombinationItem = false;
            for (AItemActor* AvailableItem : AvailableItems)
            {
                if (AvailableItem && AvailableItem->IsA(CombinationItemClass))
                {
                    bContainsCombinationItem = true;
                    break;
                }
            }

            if (!bContainsCombinationItem)
            {
                bCanCombine = false;

                // Track the wrong item in the WrongItems array
                for (AItemActor* AvailableItem : AvailableItems)
                {
                    if (AvailableItem && AvailableItem->IsA(CombinationItemClass))
                    {
                        WrongItems.Add(AvailableItem);
                        break; // Add only one instance of the item to WrongItems
                    }
                }

                // No need to continue checking other combination items if already wrong
                break;
            }
        }

        if (bCanCombine)
        {
            // Spawn the result actor at the location of BaseItem
            FActorSpawnParameters SpawnParams;
            FVector SpawnLocation = BaseItem->GetActorLocation();
            FRotator SpawnRotation = BaseItem->GetActorRotation();
            AActor* ResultActor = GetWorld()->SpawnActor<AActor>(ResultActorClass, SpawnLocation, SpawnRotation, SpawnParams);
            if (ResultActor)
            {
                // Additional logic or property settings for the ResultActor can be done here

                // Swap the newly generated item with the base item if enabled
                if (SwapWithBaseItem)
                {
                    AItemActor* NewBaseItem = Cast<AItemActor>(ResultActor);
                    if (NewBaseItem)
                    {
                        NewBaseItem->ItemCombinations = BaseItem->ItemCombinations;
                        for (UItemCombination* CombinationComponent : BaseItem->ItemCombinations)
                        {
                            CombinationComponent->BaseItem = NewBaseItem;
                        }

                        // Destroy the old base item
                        BaseItem->Destroy();
                    }
                }

                // Remove the used items from AvailableItems that are not in WrongItems
                TArray<AItemActor*> TempAvailableItems = AvailableItems;
                for (const TSubclassOf<AItemActor>& CombinationItemClass : CombinationItemClasses)
                {
                    for (AItemActor* TempAvailableItem : TempAvailableItems)
                    {
                        if (TempAvailableItem && TempAvailableItem->IsA(CombinationItemClass) && !WrongItems.Contains(TempAvailableItem))
                        {
                            TempAvailableItems.Remove(TempAvailableItem);
                            TempAvailableItem->Destroy();
                            break; // Remove only one instance of the item class
                        }
                    }
                }

                AvailableItems = TempAvailableItems; // Update the AvailableItems list

                CombinationResultInfo = TEXT("Combination successful");
                OnCombinationSucceeded();
            }
        }
        else
        {
            CombinationResultInfo = TEXT("Can't combine these items: missing required components");
            OnCombinationFailed();
        }
    }
    else
    {
        CombinationResultInfo = TEXT("No base item found for combination");
        OnCombinationFailed();
    }
}

void UItemCombination::OnItemAdded_Implementation(AItemActor* CombinationItem)
{
    // can be overwitten by blueprint
}

void UItemCombination::OnItemRemoved_Implementation(AItemActor* CombinationItem)
{
    // can be overwitten by blueprint
}



void UItemCombination::OnCombinationSucceeded_Implementation()
{
    // can be overwitten by blueprint
}

void UItemCombination::OnCombinationFailed_Implementation()
{
    // can be overwitten by blueprint
}