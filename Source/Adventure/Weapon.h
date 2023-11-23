#pragma once

#include "CoreMinimal.h"
#include "Tool.h"
#include "WeaponCrosshair.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Weapon.generated.h"

class AAdventureCharacter;
class AWeaponProjectile;


UCLASS()
class ADVENTURE_API AWeapon : public ATool
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float PrimaryMeleeDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float SecondaryMeleeDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float MeleeTraceDistance = 10.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	bool HasPrimaryCrosshair = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	bool HasSecondaryCrosshair = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	TSubclassOf<AWeaponCrosshair> PrimaryCrosshairClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	TSubclassOf<AWeaponCrosshair> SecondaryCrosshairClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	AWeaponCrosshair* PrimaryCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	AWeaponCrosshair* SecondaryCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	bool PrimaryAutoAim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	bool SecondaryAutoAim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float EgoViewCrosshairDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float ThirdPersonViewCrosshairDistance = 8000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float MapViewCrosshairDistance = 750.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float TopDownViewCrosshairDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	bool AimFromCWeaponLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "CrosshairImage"))
	UTexture2D* CrosshairImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "The static mesh component of the interaction actor"))
	UStaticMeshComponent* CrosshairMesh;


	UPROPERTY(EditDefaultsOnly, Category = "Game Weapon", meta = (ToolTip = "PrimaryProjectileClass"))
	TSubclassOf<class AWeaponProjectile> PrimaryProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game Weapon", meta = (ToolTip = "SecondaryProjectileClass"))
	TSubclassOf<class AWeaponProjectile> SecondaryProjectileClass;


	/** Primary Action */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "MussleMesh"))
	FVector PrimaryMussleOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionSound"))
	USoundBase* PrimaryActionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimation"))
	UAnimSequence* PrimaryActionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float PrimaryActionAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimation"))
	UAnimSequence* PrimaryActionCharacterAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float PrimaryActionCharacterAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "Speech Bubble Class"))
	TSubclassOf<ASpeechBubble> PrimaryActionSpeechBubbleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "Speech Bubble Class"))
	FVector PrimaryActionSpeechBubbleLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "Speech bubble of the item"))
	ASpeechBubble* PrimaryActionSpeechBubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "PrimaryActionSpeechBubbleText"))
	FString PrimaryActionSpeechBubbleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "PrimaryActionSpeechBubbleFontSize"))
	float PrimaryActionSpeechBubbleFontSize = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "PrimaryActionSpeechBubbleDuration"))
	float PrimaryActionSpeechBubbleDuration = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Speech Bubble", meta = (ToolTip = "ShowPrimaryActionSpeechBubble"))
	void ShowPrimaryActionSpeechBubble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter);

	/** Secondary Action */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "MussleMesh"))
	FVector SecondaryMussleOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionSound"))
	USoundBase* SecondaryActionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimation"))
	UAnimSequence* SecondaryActionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float SecondaryActionAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimation"))
	UAnimSequence* SecondaryActionCharacterAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "ActionAnimationRate"))
	float SecondaryActionCharacterAnimationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "Speech Bubble Class"))
	TSubclassOf<ASpeechBubble> SecondaryActionSpeechBubbleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "Speech Bubble Class"))
	FVector SecondaryActionSpeechBubbleLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Weapon", meta = (ToolTip = "Speech bubble of the item"))
	ASpeechBubble* SecondaryActionSpeechBubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "SecondaryActionSpeechBubbleText"))
	FString SecondaryActionSpeechBubbleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "SecondaryActionSpeechBubbleFontSize"))
	float SecondaryActionSpeechBubbleFontSize = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Bubble", meta = (ToolTip = "SecondaryActionSpeechBubbleDuration"))
	float SecondaryActionSpeechBubbleDuration = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "ShowSecondaryActionSpeechBubble"))
	void ShowSecondaryActionSpeechBubble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "FireMappingContext", AllowPrivateAccess = "true"))
	class UInputMappingContext* ActionMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "FireAction", AllowPrivateAccess = "true"))
	class UInputAction* PrimaryActionInput;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "FireAction", AllowPrivateAccess = "true"))
	class UInputAction* SecondaryActionInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "PrimaryAnimationTime"))
	float PrimaryAnimationTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "SecondaryAnimationTime"))
	float SecondaryAnimationTime = 0.0f;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "IsSecondaryAttacking"))
	bool IsSelected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "IsSecondaryAttacking"))
	bool SecondaryMode = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "IsPrimaryAttacking"))
	bool IsPrimaryAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Weapon", meta = (ToolTip = "IsSecondaryAttacking"))
	bool IsSecondaryAttacking = false;


	AWeapon();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "Primary action"))
	void AttachWeapon(AAdventureCharacter* TargetCharacter, bool AsPrimaryWeapon, FName AnimationSlot);

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "Primary action"))
	virtual void SetPrimaryMode(bool PrimaryActionMode);

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "Primary action"))
	virtual void Action(bool SecondaryActionMode);

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "Primary action"))
	virtual void PrimaryAction();

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "Secondary action"))
	virtual void SecondaryAction();


	virtual void PickedUpByCharacter(AAdventureCharacter* TargetCharacter, bool AsPrimaryWeapon, FName SlotName) override;

	virtual void Show() override;

	virtual void Hide() override;

	virtual void Use() override;

	virtual void Drop() override;

	void SetMeleeCollisions(bool CollisionsEnabled);



	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "GetAimLocation"))
	FVector GetAimLocation();

	UFUNCTION(BlueprintCallable, Category = "Game Weapon", meta = (ToolTip = "GetMuzzleLocation"))
	FVector GetMuzzleLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Weapon")
	void OnPrimaryAction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Game Weapon")
	void OnSecondaryAction();

protected:

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitTool() override;

public:
	virtual void Tick(float DeltaTime) override;



private:
	bool CollisionsAreEnabled = false;

};
