#pragma once

#include "CoreMinimal.h"
#include "ItemCombination.h"
#include "AdventureGameModeBase.h"
#include "PlayerInteraction.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class ADVENTURE_API UPlayerInteraction : public UObject
{
	GENERATED_BODY()
public:
	UPlayerInteraction();

	AAdventureGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interaction", meta = (ToolTip = ""))
	APlayerCharacter* InitialPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interaction", meta = (ToolTip = ""))
	APlayerCharacter* Player2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interaction", meta = (ToolTip = ""))
	APlayerCharacter* Player3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interaction", meta = (ToolTip = ""))
	APlayerCharacter* Player4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interactionr", meta = (ToolTip = ""))
	TArray<APlayerCharacter*> Players;

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "CancelInteraction"))
	virtual void CancelInteraction(APlayerCharacter* PlayerWhoCanceled);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "JoinInteraction"))
	virtual void JoinInteraction(APlayerCharacter* PlayerWhoCanceled);

	UFUNCTION(BlueprintCallable, Category = "Game Character", meta = (ToolTip = "LeaveInteraction"))
	virtual void LeaveInteraction(APlayerCharacter* PlayerWhoCanceled);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Player Interactionr", meta = (ToolTip = ""))
	UItemCombination* ItemCombination;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction Answer")
	void OnCancelInteraction(APlayerCharacter* PlayerCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction Answer")
	void OnJoinInteraction(APlayerCharacter* PlayerCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction Answer")
	void OnLeaveInteraction(APlayerCharacter* PlayerCharacter);


};
