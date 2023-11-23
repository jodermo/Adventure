// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponCrosshair.generated.h"

class AWeapon;
class AAdventureCharacter;

UCLASS()
class ADVENTURE_API AWeaponCrosshair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponCrosshair();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon Crosshair", meta = (ToolTip = "Weapon"))
	AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon Crosshair", meta = (ToolTip = "Character"))
	AAdventureCharacter* Character;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
