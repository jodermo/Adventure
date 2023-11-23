
#pragma once

#include "CoreMinimal.h"
#include <map>
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "VehicleInteractionrComponent.h"
#include "Vehicle.generated.h"

class AAdventureCharacter;
class AAdventureGameModeBase;
class AItemActor;
class ASpeechBubble;

UENUM(BlueprintType)
enum class EWheelConfiguration : uint8
{
	FWD UMETA(DisplayName = "Front-Wheel Drive"),
	RWD UMETA(DisplayName = "Rear-Wheel Drive"),
	_4WD UMETA(DisplayName = "Four-Wheel Drive")
};



UCLASS()
class ADVENTURE_API AVehicle : public APawn
{
	GENERATED_BODY()

public:
	AVehicle();

	void InitVehicle();





	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact")
	float ObjectImpactMultiplier = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact")
	float VehicleImpactReduction = 0.5f;


	void HandleImpactWithObject(const FHitResult& Hit);




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Icon for the vehicle"))
	UTexture2D* VehicleIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Name of the vehicle"))
	FString VehicleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Description of the vehicle"))
	FString VehicleDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "GameMode."))
	AAdventureGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Speech bubble of the vehicle"))
	ASpeechBubble* SpeechBubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Component responsible for character/vehicle interaction behavior"))
	UVehicleInteractionrComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle")
	EWheelConfiguration WheelConfiguration = EWheelConfiguration::FWD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "VehicleMesh."))
	UStaticMeshComponent* VehicleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Front Left Wheel"))
	UStaticMeshComponent* FrontLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Front Right Wheel"))
	UStaticMeshComponent* FrontRightWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle")
	UStaticMeshComponent* RearLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle")
	UStaticMeshComponent* RearRightWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "List of items in car"))
	TArray<AItemActor*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Armor."))
	float Armor = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Health."))
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Fuel."))
	float Fuel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Fuel."))
	float FuelConsumption = .01f;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "EnginePower."))
	float EnginePower = 2000000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "MaxSpeed."))
	float MaxSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Acceleration."))
	float Acceleration = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Damping."))
	float LateralFrictionCoefficient = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Damping."))
	float SteeringFrictionCoefficient = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max Steering Angle."))
	float MaxSteeringAngle = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max Steering Angle."))
	float SteeringSpeed = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max Steering Angle."))
	float SteeringSensitivity = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max Steering Angle."))
	float BodySteeringSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Drag Coefficient"))
	float DragCoefficient = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Damping."))
	float Resistance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Damping."))
	float AngularDamping = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Damage Multiplier"))
	float DamageMultiplier = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Bounce Force"))
	float BounceForce = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "ThrottleWithdrawal"))
	float ThrottleWithdrawal = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "SteeringWithdrawal"))
	float SteeringWithdrawal = 0.001f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "WheelbaseLength"))
	float WheelbaseLength = 240.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "WheelTrackWidth"))
	float WheelTrackWidth = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "FrontWheelRadius"))
	float FrontWheelRadius = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "RearWheelRadius"))
	float RearWheelRadius = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "RearWheelRadius"))
	float MinimumMoveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max distance to detect if vehicle is near"))
	float ImpulseMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Max distance to detect if vehicle is near"))
	float CharacterImpactMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float MaxImpactForce = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	float SuspensionRestLength = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	float SuspensionMaxDrop = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	float SuspensionCompression = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Suspension")
	float SuspensionCurrentDrop = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	float SuspensionSpringConstant = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	float SuspensionDamping = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Handbrake Friction Coefficient"))
	float HandbrakeFrictionCoefficient = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle|Handbrake", meta = (ToolTip = "Angular velocity for rear wheels during handbrake operation"))
	float HandbrakeRotationSpeed = 200.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle|Handbrake", meta = (ToolTip = "HandbrakeRotationDampingn"))
	float HandbrakeRotationDamping = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle|Handbrake", meta = (ToolTip = "HandbrakeSteeringDamping"))
	float HandbrakeSteeringDamping = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "NOS Boost Strength"))
	float NOSBoostStrength = 500000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "NOS Boost Strength"))
	float NOSLoad = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "NOS Boost Strength"))
	float NOSConsumption = 1.0f;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MinVehicleImpactForce"))
	float CameraSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MinVehicleImpactForce"))
	float CameraPitchOffset = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MinVehicleImpactForce"))
	float CameraInterpSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Location of the driver in the vehicle"))
	FVector LookAtLocation = FVector(0.0f, 800.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Location of the driver in the vehicle"))
	FVector CameraLocation = FVector(0.0f, -200.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Character", meta = (ToolTip = "MinVehicleImpactForce"))
	float DesiredCameraBoomLength = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "GravityForce"))
	FVector GravityForce = FVector(0.0f, 0.0f, -980.0f);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "Current Driver"))
	AAdventureCharacter* DriverCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode", meta = (ToolTip = "Array of top-down environmental object in the game."))
	TArray<AEnvironmentalObject*> EnvironmentalObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Location of the driver in the vehicle"))
	FVector DriverSeatLocation = FVector(0.0f, 0.0f, 160.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Location of the driver in the vehicle"))
	FVector DriverLeaveLocation = FVector(0.0f, -200.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "List of  passenge characters inside the vehicle"))
	TArray<AAdventureCharacter*> PassengerCharacters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "Number of seats in the vehicle, and locations for player to sit"))
	TArray<FVector> PassengerSeatLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Vehicle", meta = (ToolTip = "Location of the driver in the vehicle"))
	FVector PassengerLeaveLocation = FVector(0.0f, 600.0f, 100.0f);

	UPROPERTY(EditAnywhere, Category = "Game Vehicle")
	FVector CenterOfGravityLocation = FVector(0.0f, 0.0f, -50.0f); // Adjust the values based on your vehicle's dimensions

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Move Vehicle."))
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Move Vehicle."))
	void MoveRight(float Value);


	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "OnEnterVehicle."))
	void InteractWithVehicle(AAdventureCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "OnEnterVehicle."))
	void OnEnterVehicle(AAdventureCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "OnExitVehicle."))
	void OnExitVehicle(AAdventureCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "GetImpactForceMagnitude."))
	float GetImpactForceMagnitude(AAdventureCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Engage Handbrake."))
	void EngageHandbrake();
	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Release Handbrake."))
	void ReleaseHandbrake();

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Activate NOS Boost"))
	void ActivateNOS();

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "Deactivate NOS Boost"))
	void DeactivateNOS();

	FVector ForwardVelocity = FVector();
	FVector LastLocation = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "Throttle"))
	float Throttle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "RollSpeed"))
	float WheelSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "DriveSpeed"))
	float RollSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "DriveSpeed"))
	float DriveSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "ForwardAngle"))
	float ForwardAngle = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "SteeringAngle"))
	float SteeringAngle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "VehicleSpeed"))
	float VehicleSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "VehicleSpeed"))
	float VehicleSpeedKmh = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "VehicleSpeed"))
	float VehicleSpeedMph = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "EngineForce"))
	FVector EngineForce = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "DriveForce"))
	FVector DriveForce = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "SteeringForce"))
	FVector SteeringForce = FVector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "FrontWheelRotation"))
	float FrontWheelRotation = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "RearWheelRotation"))
	float RearWheelRotation = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "IsMoving"))
	bool IsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "FrontLeftWheelOnGround"))
	bool FrontLeftWheelOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "FrontRightWheelOnGround"))
	bool FrontRightWheelOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "RearLeftWheelOnGround"))
	bool RearLeftWheelOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "RearRightWheelOnGround"))
	bool RearRightWheelOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "AnyWheelOnGround"))
	bool AnyWheelOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "AllWheelsOnGround"))
	bool AllWheelsOnGround = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "HandbrakeEngaged"))
	bool HandbrakeEngaged = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Vehicle", meta = (ToolTip = "IsNOSActive"))
	bool IsNOSActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* EngineSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* TireSkidSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* BrakeSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* ThrottleSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* NOSSoundComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* HitSoundComponent;

	UFUNCTION(BlueprintCallable, Category = "Game Vehicle", meta = (ToolTip = "ShowSpeechBuuble"))
	void ShowSpeechBuuble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter);


	FVector GetLookAtLocation();

	void PlayEngineSound(float VolumeMultiplier);
	void StopEngineSound();

	void PlayTireSkidSound(float VolumeMultiplier);
	void StopTireSkidSound();

	void PlayBrakeSound(float VolumeMultiplier);
	void StopBrakeSound();

	void PlayThrottleSound(float VolumeMultiplier);
	void StopThrottleSound();

	void PlayNOSSound(float VolumeMultiplier);
	void StopNOSSound();

	void PlayHitSound(float VolumeMultiplier);
	void StopHitSound();

	AAdventureCharacter* GetDriverCharacter() const { return DriverCharacter; }

	TArray<bool> WheelsOnEnvironmentalObject;

	void InitializeWheelsOnEnvironmentalObject();
	void IsWheelOnEnvironmentalObject(UStaticMeshComponent* Wheel);

private:
	struct WheelCollisionData {
		bool IsGrounded;
		float LastCheckedTime;
		UStaticMeshComponent* Wheel;
	};

	std::map<UStaticMeshComponent*, WheelCollisionData> WheelCollisionCache;
	const float CollisionCheckInterval = 0.1f; // Time interval between checks in seconds


protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:

	UPrimitiveComponent* RootPrimitive;
	void CheckIfWheelsOnGround(float DeltaTime);
	bool WheelsOnGround(UStaticMeshComponent* Wheel);
	void UpdateRollSpeed(float DeltaTime);
	void UpdateThrottle(float DeltaTime);
	void UpdateMotor(float DeltaTime);
	void UpdateTransmission(float DeltaTime);
	void UpdateSteering(float DeltaTime);
	void UpdateSuspension(float DeltaTime);
	void UpdateHandbrake(float DeltaTime);
	void UpdateNOS(float DeltaTime);
	void UpdateEnvironmentalObjects(float DeltaTime);
	void UpdateWheels(float DeltaTime);
	void UpdateVehicle(float DeltaTime);
	void ApplyDamage(float DamageAmount);

	void ApplySteeringTorque(float Torque, UStaticMeshComponent* Wheel);

	void DestroyVehicle();

	FVector CalculateResistanceForce(const FVector& Velocity);
	FVector CalculateDragForce(const FVector& Velocity);
	FVector CalculateEngineForce(float ThrottleInput);
	void ApplyLateralFriction();

	float CalculateTurnRadius(float SteeringAngle);
	float CalculateFrontLeftSteeringAngle(float DesiredSteeringAngle);
	float CalculateFrontRightSteeringAngle(float DesiredSteeringAngle);

};
