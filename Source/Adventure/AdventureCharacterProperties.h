// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdventureCharacterProperties.generated.h"


UCLASS(Blueprintable)
class ADVENTURE_API UAdventureCharacterProperties : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdventureCharacterProperties();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Properties", meta = (ToolTip = "Name of the character"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Properties", meta = (ToolTip = "Description of the character"))
	FString Description;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
