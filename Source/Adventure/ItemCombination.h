#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemCombination.generated.h"

class AItemActor;

UCLASS(Blueprintable)
class ADVENTURE_API UItemCombination : public UActorComponent
{
	GENERATED_BODY()

public:	

	UItemCombination();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Name for this combination"))
	FString CombinationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Description for this combination"))
	FString CombinationDescription;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Image for this combination"))
	UTexture2D* CombinationImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Info message for last combination action"))
	FString CombinationResultInfo;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Owner actor for combination"))
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Base item for combination"))
	AItemActor* BaseItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Collected items for combination"))
	TArray<AItemActor*> AvailableItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Combination", meta = (ToolTip = "Wrong items for combination"))
	TArray<AItemActor*> WrongItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Items needed to generate result actor."))
	TArray<TSubclassOf<AItemActor>> CombinationItemClasses;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Result actor, generated when all combined items are available."))
	TSubclassOf<AActor> ResultActorClass;

	UFUNCTION(BlueprintCallable, Category = "Item Combination", meta = (ToolTip = "Add item to available items for combination"))
	void AddItem(AItemActor* CombinationItem);

	UFUNCTION(BlueprintCallable, Category = "Item Combination", meta = (ToolTip = "Remove item from available items for combination"))
	void RemoveItem(AItemActor* CombinationItem);

	UFUNCTION(BlueprintCallable, Category = "Item Combination", meta = (ToolTip = "Trigger item combination"))
	void CombineItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Swap new generated item with base item"))
	bool RomeItemsAfter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Combination", meta = (ToolTip = "Swap new generated item with base item"))
	bool SwapWithBaseItem = false;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Combination")
	void OnItemAdded(AItemActor* CombinationItem);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Combination")
	void OnItemRemoved(AItemActor* CombinationItem);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Combination")
	void OnCombinationSucceeded();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Combination")
	void OnCombinationFailed();

protected:
	virtual void BeginPlay() override;

	virtual void InitComponent();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
