
#pragma once

#include "CoreMinimal.h"
#include "AdventureCharacter.h"
#include "PlayerInteraction.h"
#include "PlayerCharacterProperties.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ADVENTURE_API APlayerCharacter : public AAdventureCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character", meta = (ToolTip = "Name of the player"))
	FString PlayerName;

	virtual void Die() override;
	virtual void OnAreaOverlapBegin(AAreaActor* AreaActor) override;
	virtual void OnAreaOverlapEnd(AAreaActor* AreaActor) override;
	virtual void MenuAccept() override;
	virtual void MenuDeny() override;
	virtual void MenuPrevTab() override;
	virtual void MenuNextTab() override;
	virtual void MenuPrevOption() override;
	virtual void MenuNextOption() override;
	virtual bool CharacterCanMove() override;
	virtual bool CanAttackCharacter(AAdventureCharacter* Character) override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character", meta = (ToolTip = "MaxPlayerInteractionDistance"))
	float MaxPlayerInteractionDistance = 500;

	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "NewPlayerInteraction"))
	virtual void NewPlayerInteraction();

	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "SelectPlayerInteraction"))
	virtual void SelectPlayerInteraction(UPlayerInteraction* PlayerInteraction);


	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "SelectPrevPlayerInteraction"))
	virtual void SelectPrevPlayerInteraction();


	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "SelcetNextPlayerInteraction"))
	virtual void SelcetNextPlayerInteraction();



	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "JoinPlayerInteraction"))
	virtual void JoinPlayerInteraction(UPlayerInteraction* PlayerInteraction);

	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "CancelPlayerInteraction"))
	virtual void CancelPlayerInteraction();

	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "CancelPlayerInteraction"))
	virtual void ShowPlayerInteractionSelection();

	UFUNCTION(BlueprintCallable, Category = "Player Character", meta = (ToolTip = "CancelPlayerInteraction"))
	virtual void HidePlayerInteractionSelection();

	virtual void UpdateNearPlayerInteractions(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Character", meta = (ToolTip = "CurrentPlayerInteraction"))
	UPlayerInteraction* SelectedPlayerInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Character", meta = (ToolTip = "CurrentPlayerInteraction"))
	UPlayerInteraction* CurrentPlayerInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Character", meta = (ToolTip = "NearPlayerInteractions"))
	TArray<UPlayerInteraction*> NearPlayerInteractions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character", meta = (ToolTip = "MaxPlayerInteractionDistance"))
	float PlayerInteractionSelectionVisible = false;

protected: 
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
