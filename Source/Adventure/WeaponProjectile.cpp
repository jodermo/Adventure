#include "WeaponProjectile.h"
#include "AdventureCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AWeaponProjectile::AWeaponProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AWeaponProjectile::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	InitProjectile();
}

void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	InitProjectile();
}

void AWeaponProjectile::InitProjectile()
{
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = LifeSpan;
}

void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor == this) || (OtherActor == Weapon) || (IgnorePlayerCharacter && OtherActor == Weapon->Character))
	{
		return;
	}
	AAdventureCharacter* OtherCharacter = Cast<AAdventureCharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->TakeDamageAtLocation(ImpulseStength * CharacterDamageFactor, GetActorLocation(), GetVelocity(), this);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * ImpulseStength, GetActorLocation());
	}

	if (!ReboundFromTarget)
	{
		Destroy();
	}
	else if (MaxReboundNumber)
	{
		if (Rebounds >= MaxReboundNumber)
		{
			Destroy();
		}
		else
		{
			Rebounds++;
		}
	}
}