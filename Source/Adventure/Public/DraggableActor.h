
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DraggableActor.generated.h"

class AAdventureGameModeBase;
class AGameCharacter;

UCLASS()
class ADVENTURE_API ADraggableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADraggableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	FString ActorName;

	AAdventureGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	UStaticMeshComponent* RootMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	bool Draggable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	bool CanHitPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	float MinHitImpulseStrength = 10.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	int DestroyAfterHits = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Draggable Actor")
	int ObjectHits = 0;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor")
	virtual void DestroyDraggableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	FVector DragLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	float ThrowForceFactor = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	float ThrowImpulseStength = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor")
	float ThrowDamageFactor = 1.0f;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Slots", meta = (ToolTip = "DraggableActorSlot"))
	FName CharacterDraggableActorSlot = FName("DraggableActor");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Draggable Actor")
	AGameCharacter* LastDragCharacter;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor")
	virtual void GetsGrabbed(AGameCharacter* ByCharacter);

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor")
	virtual void GetsDropped(AGameCharacter* ByCharacter);

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor")
	virtual void GetsThrown(AGameCharacter* ByCharacter, FVector TargetLocation);




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* DragParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector DragParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* DragCharacterParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector DragCharacterParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UAudioComponent* DragSoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor Effects")
	virtual void TriggerDragEffects(AGameCharacter* ByCharacter, bool PlaySound);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* DropParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector DropParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* DropCharacterParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector DropCharacterParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UAudioComponent* DropSoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor Effects")
	virtual void TriggerDropEffects(AGameCharacter* ByCharacter, bool PlaySound);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* ThrowParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector ThrowParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* ThrowCharacterParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector ThrowCharacterParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UAudioComponent* ThrowSoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor Effects")
	virtual void TriggerThrowEffects(AGameCharacter* ByCharacter, bool PlaySound);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector HitParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* HitCharacterParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector HitCharacterParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UAudioComponent* HitSoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor Effects")
	virtual void TriggerHitEffects(AGameCharacter* TargetCharacter, bool PlaySound);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UNiagaraSystem* DestroyParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	FVector DestroyParticlesLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draggable Actor Effects")
	UAudioComponent* DestroySoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Draggable Actor Effects")
	virtual void TriggerDestroyEffects(bool PlaySound);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:
	void InitDraggableActor();

	ECollisionEnabled::Type InitialCollisionProfile = ECollisionEnabled::QueryAndPhysics;
};
