// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdventureCharacterProperties.h"
#include "PlayerCharacterProperties.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ADVENTURE_API UPlayerCharacterProperties : public UAdventureCharacterProperties
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Properties", meta = (ToolTip = "Name of the team"))
	FString TeamName;
	
};
