// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h" 
#include "CharacterWidget.generated.h"


class AGameCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class ADVENTURE_API UCharacterWidget : public UWidgetComponent
{
	GENERATED_BODY()

public:
	AGameCharacter* Character;
	
};
