#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

class AWeapon;
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class ADVENTURE_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	float InitialSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	float MaxSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	float LifeSpan = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	float ImpulseStength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	float CharacterDamageFactor = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	bool ReboundFromTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	int MaxReboundNumber = 0;

	int Rebounds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Projectile", meta = (ToolTip = "InitialSpeed"))
	bool IgnorePlayerCharacter = false;



	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	AWeaponProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

};
