
#include "Vehicle.h"
#include "AdventureGameModeBase.h"
#include "AdventureCharacter.h"
#include "EnvironmentalObject.h"

AVehicle::AVehicle()
{
    PrimaryActorTick.bCanEverTick = true;
    InteractionComponent = CreateDefaultSubobject<UVehicleInteractionrComponent>(TEXT("InteractionComponent"));
    VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
    VehicleMesh->SetCollisionProfileName(TEXT("VehicleCollision"));
    VehicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    VehicleMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    VehicleMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    RootComponent = VehicleMesh;
    FrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftWheel"));
    FrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightWheel"));
    RearLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearLeftWheel"));
    RearRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearRightWheel"));
    FrontLeftWheel->SetupAttachment(RootComponent);
    FrontRightWheel->SetupAttachment(RootComponent);
    RearLeftWheel->SetupAttachment(RootComponent);
    RearRightWheel->SetupAttachment(RootComponent);
    EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSoundComponent"));
    EngineSoundComponent->bAutoActivate = false;
    EngineSoundComponent->SetupAttachment(RootComponent);
    TireSkidSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TireSkidSoundComponent"));
    TireSkidSoundComponent->bAutoActivate = false;
    TireSkidSoundComponent->SetupAttachment(RootComponent);
    BrakeSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BrakeSoundComponent"));
    BrakeSoundComponent->bAutoActivate = false;
    BrakeSoundComponent->SetupAttachment(RootComponent);
    ThrottleSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ThrottleSoundComponent"));
    ThrottleSoundComponent->bAutoActivate = false;
    ThrottleSoundComponent->SetupAttachment(RootComponent);
    NOSSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("NOSSoundComponent"));
    NOSSoundComponent->bAutoActivate = false;
    NOSSoundComponent->SetupAttachment(RootComponent);
    HitSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSoundComponent"));
    HitSoundComponent->bAutoActivate = false;
    HitSoundComponent->SetupAttachment(RootComponent);
}

void AVehicle::BeginPlay()
{
	Super::BeginPlay();
    InitVehicle();
    LastLocation = GetActorLocation();
    if (VehicleMesh)
    {
        VehicleMesh->BodyInstance.COMNudge = CenterOfGravityLocation;
    }
}

void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateEnvironmentalObjects(DeltaTime);
    CheckIfWheelsOnGround(DeltaTime);
    UpdateSuspension(DeltaTime);
    UpdateThrottle(DeltaTime);
    UpdateMotor(DeltaTime);
    UpdateTransmission(DeltaTime);
    UpdateSteering(DeltaTime);
    UpdateWheels(DeltaTime);
    UpdateRollSpeed(DeltaTime);
    UpdateHandbrake(DeltaTime);

    UpdateNOS(DeltaTime);
    UpdateVehicle(DeltaTime);
}

void AVehicle::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{


    bool IgnoreHit = false;

    if (IsMoving && DriverCharacter)
    {
        FVector RelativeVelocity = GetVelocity() - Other->GetVelocity();
        FVector ImpactDirection = Hit.ImpactNormal * -1.0f;
        FVector ImpactForce = ImpactDirection * ImpulseMultiplier;
        float Damage = ImpactForce.GetMax();
        AAdventureCharacter* Character = Cast<AAdventureCharacter>(Other);
        if (Character )
        {
            Damage = FVector::DotProduct(RelativeVelocity, HitNormal) * RootPrimitive->GetMass() * Character->GetCapsuleComponent()->GetMass();
            if (Damage > Character->MinVehicleImpactForce) {
         
                Damage *= Character->VehicleImpactMultiplier * CharacterImpactMultiplier;
                Character->TakeDamageAtLocation(Damage, Hit.ImpactPoint, ImpactForce, this);
                IgnoreHit = true;
            }

            float VolumeMultiplier = FMath::Clamp(Damage / MaxImpactForce, 0.0f, 1.0f);
            PlayHitSound(VolumeMultiplier);
        }
        if (!IgnoreHit) 
        {
            Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
        }
    }
    else 
    {
        HandleImpactWithObject(Hit);
        Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
    }



  
}

void AVehicle::HandleImpactWithObject(const FHitResult& Hit)
{
    UPrimitiveComponent* HitComponent = Hit.GetComponent();
    if (HitComponent && HitComponent->IsSimulatingPhysics())
    {
        // Calculate the force to apply to the object
        FVector ImpactForce = Hit.ImpactNormal * -1.0f * ObjectImpactMultiplier;

        // Apply force to the object
        HitComponent->AddImpulseAtLocation(ImpactForce, Hit.ImpactPoint);
    }

    // Reduce the impact force for the vehicle itself
    UPrimitiveComponent* VehicleComponent = Cast<UPrimitiveComponent>(GetRootComponent());
    if (VehicleComponent && VehicleComponent->IsSimulatingPhysics())
    {
        FVector VehicleImpactForce = Hit.ImpactNormal * VehicleImpactReduction;
        VehicleComponent->AddImpulseAtLocation(VehicleImpactForce, Hit.ImpactPoint);
    }
}

void AVehicle::InitVehicle()
{
    AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
    if (GameMode)
    {
        GameMode->Vehicles.Add(this);
    }
    RootPrimitive = Cast<UPrimitiveComponent>(RootComponent);
}

void AVehicle::MoveForward(float Value)
{
    Throttle = Value;
}

void AVehicle::MoveRight(float Value)
{
    float IncrementalSteeringAngle = Value * MaxSteeringAngle * SteeringSpeed;
    SteeringAngle = FMath::Clamp(SteeringAngle + IncrementalSteeringAngle, -MaxSteeringAngle, MaxSteeringAngle);
}

FVector AVehicle::CalculateResistanceForce(const FVector& Velocity)
{
    return -Resistance * Velocity;
}

FVector AVehicle::CalculateDragForce(const FVector& Velocity)
{
    return -Velocity.GetSafeNormal() * (DragCoefficient * Velocity.SizeSquared());
}

FVector AVehicle::CalculateEngineForce(float ThrottleInput)
{
    float DesiredAcceleration = ThrottleInput * EnginePower * Acceleration;
    return GetActorForwardVector() * DesiredAcceleration;
}

void AVehicle::ApplyLateralFriction()
{
    FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
    FVector LateralVelocity = CurrentPhysicsVelocity - CurrentPhysicsVelocity.ProjectOnTo(GetActorForwardVector());
    FVector LateralFriction = -LateralVelocity.GetSafeNormal() * LateralVelocity.Size() * LateralFrictionCoefficient;
    RootPrimitive->AddForce(LateralFriction);
}

void AVehicle::UpdateThrottle(float DeltaTime)
{
    FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
    FVector ResistanceForce = CalculateResistanceForce(CurrentPhysicsVelocity);
    FVector DragForce = CalculateDragForce(CurrentPhysicsVelocity);
    if (Fuel > 0.0f) 
    {
        if (Throttle > 0.0f)
        {
            EngineForce = CalculateEngineForce(Throttle);

        }
        else if (Throttle < 0.0f)
        {
            EngineForce = CalculateEngineForce(Throttle);
        }
        else
        {
            EngineForce = FVector::ZeroVector;
        }
        if (Throttle != 0.0f)
        {
            DriveForce = EngineForce + ResistanceForce + DragForce;
            PlayThrottleSound(1.0f);
        }
        else
        {
            DriveForce = FVector::ZeroVector;
            StopThrottleSound();
        }
        Throttle = FMath::FInterpTo(Throttle, 0.0f, DeltaTime, ThrottleWithdrawal);
    }
    else 
    {
        Throttle = 0.0f;
        EngineForce = FVector::ZeroVector;
        DriveForce = EngineForce + ResistanceForce + DragForce;
        StopThrottleSound();
        StopEngineSound();
    }
}

void AVehicle::UpdateMotor(float DeltaTime)
{
    if (RootPrimitive)
    {
        float LocalDriveSpeed = FVector::DotProduct(DriveForce, GetActorForwardVector());
        DriveSpeed = LocalDriveSpeed;
        WheelSpeed = DriveSpeed;
        if (DriveSpeed < 0.0f) 
        {
            WheelSpeed = -WheelSpeed;
        }
        if (RollSpeed > WheelSpeed)
        {
            WheelSpeed = RollSpeed;
        }
        float ConsumptionThisFrame = WheelSpeed * FuelConsumption / 100000 * DeltaTime;
        if (LocalDriveSpeed > 0.0f) 
        {
            Fuel -= ConsumptionThisFrame;
            Fuel = FMath::Max(Fuel, 0.0f);
        }
    }
}

void AVehicle::CheckIfWheelsOnGround(float DeltaTime)
{
    EnvironmentalObjects.Empty();
    FrontLeftWheelOnGround = WheelsOnGround(FrontLeftWheel);
    FrontRightWheelOnGround = WheelsOnGround(FrontRightWheel);
    RearLeftWheelOnGround = WheelsOnGround(RearLeftWheel);
    RearRightWheelOnGround = WheelsOnGround(RearRightWheel);
    if (FrontLeftWheelOnGround || FrontRightWheelOnGround || RearLeftWheelOnGround || RearRightWheelOnGround)
    {
        AnyWheelOnGround = true;
    }
    if (FrontLeftWheelOnGround && FrontRightWheelOnGround && RearLeftWheelOnGround && RearRightWheelOnGround)
    {
        AllWheelsOnGround = true;
    }
}

bool AVehicle::WheelsOnGround(UStaticMeshComponent* Wheel)
{
    FVector WheelLocation = Wheel->GetComponentLocation();
    FVector TraceStart = WheelLocation;
    FVector TraceEnd = WheelLocation - FVector(0, 0, SuspensionMaxDrop);
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams);
    if (bSuccess && HitResult.GetActor())
    {
       if (GameMode)
       {
           if (GameMode->EnvironmentalObjects.Contains(HitResult.GetActor()))
           {
               AEnvironmentalObject* HitObject = Cast<AEnvironmentalObject>(HitResult.GetActor());
                   if (HitObject)
                   {
                       EnvironmentalObjects.Add(HitObject);
                   }
           }
       }
    }
    return bSuccess;
}

float AVehicle::CalculateTurnRadius(float Angle)
{
    float SteeringAngleRad = FMath::DegreesToRadians(SteeringAngle);
    float EffectiveTrackWidth = 0.5f * (FrontLeftWheel->GetSocketLocation(TEXT("FrontLeftWheelSocket")).Y - FrontRightWheel->GetSocketLocation(TEXT("FrontRightWheelSocket")).Y);
    return EffectiveTrackWidth / FMath::Tan(SteeringAngleRad);
}

void AVehicle::UpdateRollSpeed(float DeltaTime)
{
    float TotalForwardSpeed = 0.0f;
    int32 NumWheelsOnGround = 0;
    TArray<UStaticMeshComponent*> WheelsArray = { FrontLeftWheel, FrontRightWheel, RearLeftWheel, RearRightWheel };
    for (UStaticMeshComponent* Wheel : WheelsArray)
    {
        if (WheelsOnGround(Wheel))
        {
            FVector WheelVelocity = Wheel->GetPhysicsLinearVelocity();
            float ForwardSpeed = FVector::DotProduct(WheelVelocity, GetActorForwardVector());
            TotalForwardSpeed += ForwardSpeed;
            NumWheelsOnGround++;
        }
    }

    if (NumWheelsOnGround > 0)
    {
        float AverageForwardSpeed = TotalForwardSpeed / NumWheelsOnGround;
        RollSpeed = AverageForwardSpeed / DeltaTime;
    }
    else
    {
        RollSpeed = 0.0f;
    }
}

float AVehicle::CalculateFrontLeftSteeringAngle(float DesiredSteeringAngle)
{
    float TurnRadius = CalculateTurnRadius(DesiredSteeringAngle);
    return FMath::Atan2(WheelbaseLength, TurnRadius - WheelTrackWidth / 2);
}

float AVehicle::CalculateFrontRightSteeringAngle(float DesiredSteeringAngle)
{
    float TurnRadius = CalculateTurnRadius(DesiredSteeringAngle);
    return FMath::Atan2(WheelbaseLength, TurnRadius + WheelTrackWidth / 2);
}

void AVehicle::UpdateTransmission(float DeltaTime)
{
    TArray<UStaticMeshComponent*> AllWheels = { FrontLeftWheel, FrontRightWheel, RearLeftWheel, RearRightWheel };
    AnyWheelOnGround = false;
    for (UStaticMeshComponent* Wheel : AllWheels)
    {
        FVector WheelLocation = Wheel->GetComponentLocation();
        FVector RayStart = WheelLocation;
        FVector RayEnd = WheelLocation - FVector::UpVector * SuspensionMaxDrop;
        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);
        if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams))
        {
            if (HitResult.IsValidBlockingHit())
            {
                AnyWheelOnGround = true;
            }
        }
    }
    if (AnyWheelOnGround)
    {
        FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
        FVector WheelForce = (Fuel > 0.0f) ? EngineForce : FVector::ZeroVector;
        RootPrimitive->AddForce(WheelForce);
        FVector LateralVelocity = CurrentPhysicsVelocity - ForwardVelocity;
        FVector LateralFriction = -LateralVelocity.GetSafeNormal() * LateralVelocity.Size() * LateralFrictionCoefficient;



        RootPrimitive->AddForce(LateralFriction);
        if (WheelConfiguration == EWheelConfiguration::FWD)
        {
            FrontWheelRotation = (Fuel > 0.0f) ? WheelSpeed : RollSpeed;
            RearWheelRotation = RollSpeed;
            if (FrontLeftWheelOnGround)
            {
                FrontLeftWheel->AddForce(WheelForce);
            }
            if (FrontRightWheelOnGround)
            {
                FrontRightWheel->AddForce(WheelForce);
            }
        }
        else if (WheelConfiguration == EWheelConfiguration::RWD)
        {
            FrontWheelRotation = RollSpeed;
            RearWheelRotation = (Fuel > 0.0f) ? WheelSpeed : RollSpeed;
            if (RearLeftWheelOnGround)
            {
                RearLeftWheel->AddForce(WheelForce);
            }
            if (RearRightWheelOnGround)
            {
                RearRightWheel->AddForce(WheelForce);
            }
        }
        else if (WheelConfiguration == EWheelConfiguration::_4WD)
        {
            FrontWheelRotation = ((Fuel > 0.0f) ? WheelSpeed : RollSpeed) / 2;
            RearWheelRotation = ((Fuel > 0.0f) ? WheelSpeed : RollSpeed) / 2;
            if (FrontLeftWheelOnGround)
            {
                FrontLeftWheel->AddForce(WheelForce / 2);
            }
            if (FrontRightWheelOnGround)
            {
                FrontRightWheel->AddForce(WheelForce / 2);
            }
            if (RearLeftWheelOnGround)
            {
                RearLeftWheel->AddForce(WheelForce / 2);

            }
            if (RearRightWheelOnGround)
            {
                RearRightWheel->AddForce(WheelForce / 2);
            }
        }
    }
   /*
   * 
   *     if (!FrontLeftWheelOnGround) {
        FrontLeftWheel->AddForce(GravityForce);
    }
    if (!FrontRightWheelOnGround) {
        FrontRightWheel->AddForce(GravityForce);
    }
    if (!RearLeftWheelOnGround) {
        RearLeftWheel->AddForce(GravityForce);
    }
    if (!RearRightWheelOnGround) {
        RearRightWheel->AddForce(GravityForce);
    }

   */

    FrontLeftWheel->AddForce(GravityForce);
    FrontRightWheel->AddForce(GravityForce);
    RearLeftWheel->AddForce(GravityForce);
    RearRightWheel->AddForce(GravityForce);
    if (RootPrimitive)
    {
        RootPrimitive->AddForce(GravityForce);
    }


    FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
    ForwardVelocity = FVector::DotProduct(CurrentPhysicsVelocity, GetActorForwardVector()) * GetActorForwardVector();
    IsMoving = ForwardVelocity.SizeSquared() > (MinimumMoveSpeed * MinimumMoveSpeed);
}
/*

void AVehicle::UpdateSteering(float DeltaTime)
{
    if (IsMoving && AnyWheelOnGround)
    {
        FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
        float ForwardSpeed = FVector::DotProduct(CurrentPhysicsVelocity, GetActorForwardVector());
        float FrontLeftAngle = CalculateFrontLeftSteeringAngle(SteeringAngle);
        float FrontRightAngle = CalculateFrontRightSteeringAngle(SteeringAngle);
        float SteeringTorqueLeft = FrontLeftAngle * MaxSteeringAngle * SteeringSensitivity * ForwardSpeed;
        float SteeringTorqueRight = FrontRightAngle * MaxSteeringAngle * SteeringSensitivity * ForwardSpeed;
        if (FrontLeftWheel->IsSimulatingPhysics() && FrontLeftWheelOnGround)
        {
            FrontLeftWheel->AddTorqueInRadians(FVector(0, 0, SteeringTorqueLeft));
        }
        if (FrontRightWheel->IsSimulatingPhysics() && FrontRightWheelOnGround)
        {
            FrontRightWheel->AddTorqueInRadians(FVector(0, 0, SteeringTorqueRight));
        }
        if (RootPrimitive)
        {
            float DesiredAngularVelocity = SteeringAngle * SteeringSensitivity;
            float DampedAngularVelocity = DesiredAngularVelocity - AngularDamping * DesiredAngularVelocity * DeltaTime;
            FVector AngularVelocity = FVector(0, 0, DampedAngularVelocity);
            RootPrimitive->SetPhysicsAngularVelocityInDegrees(AngularVelocity);
            SteeringForce = GetActorRightVector() * SteeringAngle * SteeringFrictionCoefficient * DriveSpeed;
            RootPrimitive->AddForce(SteeringForce);
            if (ForwardVelocity.SizeSquared() > 0)
            {
                float RotationChange = SteeringAngle * DeltaTime * BodySteeringSpeed;
                FRotator NewRotation = GetActorRotation() + FRotator(0, RotationChange, 0);
                SetActorRotation(NewRotation);
            }
        }
    }

    SteeringAngle = FMath::FInterpTo(SteeringAngle, 0.0f, DeltaTime, SteeringWithdrawal);
}
*/

void AVehicle::UpdateSteering(float DeltaTime)
{
    if (IsMoving && AnyWheelOnGround)
    {
        FVector CurrentPhysicsVelocity = RootPrimitive->GetPhysicsLinearVelocity();
        float ForwardSpeed = FVector::DotProduct(CurrentPhysicsVelocity, GetActorForwardVector());
        float SteeringDorceAngle = SteeringAngle;
        if (Throttle < 0.0f)
        {
            SteeringDorceAngle = -SteeringDorceAngle;
        }
        float FrontLeftAngle = CalculateFrontLeftSteeringAngle(SteeringDorceAngle);
        float FrontRightAngle = CalculateFrontRightSteeringAngle(SteeringDorceAngle);
        float SteeringTorqueLeft = FrontLeftAngle * MaxSteeringAngle * SteeringSensitivity * ForwardSpeed;
        float SteeringTorqueRight = FrontRightAngle * MaxSteeringAngle * SteeringSensitivity * ForwardSpeed;
        if (FrontLeftWheel->IsSimulatingPhysics() && FrontLeftWheelOnGround)
        {
            FrontLeftWheel->AddTorqueInRadians(FVector(0, 0, SteeringTorqueLeft));
        }
        if (FrontRightWheel->IsSimulatingPhysics() && FrontRightWheelOnGround)
        {
            FrontRightWheel->AddTorqueInRadians(FVector(0, 0, SteeringTorqueRight));
        }
        if (RootPrimitive)
        {
            float DesiredAngularVelocity = SteeringDorceAngle * SteeringSensitivity;
            float DampedAngularVelocity = DesiredAngularVelocity - AngularDamping * DesiredAngularVelocity * DeltaTime;
            FVector AngularVelocity = FVector(0, 0, DampedAngularVelocity);
            RootPrimitive->SetPhysicsAngularVelocityInDegrees(AngularVelocity);
            SteeringForce = GetActorRightVector() * SteeringDorceAngle * SteeringFrictionCoefficient * DriveSpeed;
            RootPrimitive->AddForce(SteeringForce);
            if (ForwardVelocity.SizeSquared() > 0)
            {
                float RotationChange = SteeringDorceAngle * DeltaTime * BodySteeringSpeed;
                FRotator NewRotation = GetActorRotation() + FRotator(0, RotationChange, 0);
                SetActorRotation(NewRotation);
            }
        }
    }
    SteeringAngle = FMath::FInterpTo(SteeringAngle, 0.0f, DeltaTime, SteeringWithdrawal);
}

void AVehicle::ApplySteeringTorque(float Torque, UStaticMeshComponent* Wheel)
{
    if (Wheel->IsSimulatingPhysics() && WheelsOnGround(Wheel))
    {
        Wheel->AddTorqueInRadians(FVector(0, 0, Torque));
    }
}

void AVehicle::UpdateSuspension(float DeltaTime)
{
    if (AnyWheelOnGround)
    {
        float TargetSuspensionLength = SuspensionRestLength - SuspensionCompression * SuspensionMaxDrop;
        float CurrentSuspensionLength = SuspensionRestLength - (SuspensionCurrentDrop * SuspensionMaxDrop);
        float SuspensionDelta = TargetSuspensionLength - CurrentSuspensionLength;
        FVector SuspensionForce = FVector(0.0f, 0.0f, SuspensionDelta * SuspensionSpringConstant);
        RootPrimitive->AddForce(SuspensionForce);
        SuspensionCurrentDrop = FMath::FInterpTo(SuspensionCurrentDrop, SuspensionCompression, DeltaTime, SuspensionDamping);
    }
    else
    {
        SuspensionCurrentDrop = 0.0f;
    }
}

void AVehicle::UpdateEnvironmentalObjects(float DeltaTime)
{
    for (AEnvironmentalObject* EnvironmentalObject : EnvironmentalObjects)
    {
        InteractionComponent->DoObjectInteraction(EnvironmentalObject, DeltaTime);
    }
}

void AVehicle::UpdateWheels(float DeltaTime)
{
    if (IsMoving)
    {
        float FrontWheelCircumference = 2.0f * PI * FrontWheelRadius;
        float RearWheelCircumference = 2.0f * PI * RearWheelRadius;
        float FrontWheelDriveAngularVelocity = DriveSpeed / FrontWheelCircumference;
        float FrontWheelRollAngularVelocity = RollSpeed / FrontWheelCircumference;
        float RadiusRatio = FrontWheelRadius / RearWheelRadius;
        float RearWheelDriveAngularVelocity = DriveSpeed / RearWheelCircumference;
        float RearWheelRollAngularVelocity = RollSpeed / RearWheelCircumference;
        FVector FrontWheelAngularVelocityVector(0, 0, FrontWheelDriveAngularVelocity + FrontWheelRollAngularVelocity);
        FVector RearWheelAngularVelocityVector(0, 0, RearWheelDriveAngularVelocity + RearWheelRollAngularVelocity);
        FVector ZeroAngularVelocityVector(0, 0, 0);
        if ((WheelConfiguration == EWheelConfiguration::FWD || WheelConfiguration == EWheelConfiguration::_4WD) && Fuel > 0.0f) 
        {
            FrontLeftWheel->SetRelativeRotation(FRotator(FrontWheelDriveAngularVelocity, SteeringAngle, 0));
            FrontRightWheel->SetRelativeRotation(FRotator(FrontWheelDriveAngularVelocity, SteeringAngle, 0));

            FrontLeftWheel->SetPhysicsAngularVelocityInDegrees(FrontWheelAngularVelocityVector);
            FrontRightWheel->SetPhysicsAngularVelocityInDegrees(FrontWheelAngularVelocityVector);
        }
        else
        {
            FrontLeftWheel->SetRelativeRotation(FRotator(FrontWheelRollAngularVelocity, SteeringAngle, 0));
            FrontRightWheel->SetRelativeRotation(FRotator(FrontWheelRollAngularVelocity, SteeringAngle, 0));
        }
        if (!HandbrakeEngaged)
        {
            if (Fuel > 0.0f && WheelConfiguration == EWheelConfiguration::RWD || WheelConfiguration == EWheelConfiguration::_4WD) 
            {
                RearLeftWheel->SetRelativeRotation(FRotator(RearWheelDriveAngularVelocity, 0, 0));
                RearRightWheel->SetRelativeRotation(FRotator(RearWheelDriveAngularVelocity, 0, 0));
                RearLeftWheel->SetPhysicsAngularVelocityInDegrees(RearWheelAngularVelocityVector);
                RearRightWheel->SetPhysicsAngularVelocityInDegrees(RearWheelAngularVelocityVector);
            }
            else
            {
                RearLeftWheel->SetRelativeRotation(FRotator(RearWheelRollAngularVelocity, 0, 0));
                RearRightWheel->SetRelativeRotation(FRotator(RearWheelRollAngularVelocity, 0, 0));
                RearLeftWheel->SetPhysicsAngularVelocityInDegrees(ZeroAngularVelocityVector);
                RearRightWheel->SetPhysicsAngularVelocityInDegrees(ZeroAngularVelocityVector);
            }
        }
        else 
        {
            RearLeftWheel->SetPhysicsAngularVelocityInDegrees(ZeroAngularVelocityVector);
            RearRightWheel->SetPhysicsAngularVelocityInDegrees(ZeroAngularVelocityVector);
        }
        PlayTireSkidSound(.1f);
    }
    else 
    {
        StopTireSkidSound();
    }
}


void AVehicle::UpdateVehicle(float DeltaTime)
{
    if (RootPrimitive)
    {
        FVector CurrentVelocity = RootPrimitive->GetPhysicsLinearVelocity();
        float SpeedCmPerSec = CurrentVelocity.Size();
        VehicleSpeedKmh = SpeedCmPerSec * 0.036f;
        VehicleSpeedMph = SpeedCmPerSec * 0.022f;
        VehicleSpeed = SpeedCmPerSec; 
    }
}

void AVehicle::ApplyDamage(float DamageAmount)
{
    if (Armor > 0.0f) {
        Armor -= DamageAmount;
    }
    else 
    {
        Armor = 0.0f;
        Health -= DamageAmount;
        if (Health <= 0.0f)
        {
            DestroyVehicle();
        }
    }
}

void AVehicle::DestroyVehicle()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    StopEngineSound();
    StopTireSkidSound();
    StopBrakeSound();
    StopThrottleSound();
    StopNOSSound();
    StopHitSound();
    SetLifeSpan(0.1f);
}

void AVehicle::InteractWithVehicle(AAdventureCharacter* Character)
{
    if (!Character)
    {
        return;
    }
    InteractionComponent->DoCharacterInteraction(Character, 0.0f);
}

void AVehicle::OnEnterVehicle(AAdventureCharacter* Character)
{
    if (!Character)
    {
        return;
    }
    if (!DriverCharacter || (PassengerCharacters.Num() && PassengerCharacters.Num() < PassengerSeatLocations.Num()))
    {
        bool IsDriver = !DriverCharacter;
        FName TargetSocketName = IsDriver ? TEXT("DriverSeatSocket") : TEXT("PassengerSeatSocket");
        FVector TargetSocketLocation = VehicleMesh->GetSocketLocation(TargetSocketName);
        FRotator TargetSocketRotation = VehicleMesh->GetSocketRotation(TargetSocketName);
        FVector CharacterLocation = IsDriver ? DriverSeatLocation : PassengerLeaveLocation;
        Character->SetActorLocationAndRotation(CharacterLocation, TargetSocketRotation);
        FName AttachSocketName = IsDriver ? TEXT("DriverSocket") : TEXT("PassengerSeatSocket");
        Character->AttachToComponent(VehicleMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocketName);
        Character->CurrentVehicle = this;
        Character->SetActorEnableCollision(false);
        if (IsDriver)
        {
            DriverCharacter = Character;
            PlayEngineSound(1.0f);
        }
        else
        {
            PassengerCharacters.Add(Character);
        }
    }
    Character->OnEnterVehicle(this);
}

void AVehicle::OnExitVehicle(AAdventureCharacter* Character)
{
    bool IsInVehicle = false;
    if (Character && Character == DriverCharacter)
    {
        IsInVehicle = true;
        DriverCharacter = nullptr;
        StopEngineSound();
    }else if (PassengerCharacters.Contains(Character))
    {
        IsInVehicle = true;
        PassengerCharacters.Remove(Character);
    }
    if (IsInVehicle) 
    {
        Character->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Character->SetActorEnableCollision(true);
        Character->SetActorHiddenInGame(false);
        Character->SetActorLocation(GetActorLocation() + DriverLeaveLocation);
        Character->SetOwner(nullptr);
        Character->CurrentVehicle = nullptr;
    }
}

float AVehicle::GetImpactForceMagnitude(AAdventureCharacter* Character)
{
    if (!Character)
    {
        return 0.0f;
    }
    FVector RelativeVelocity = ForwardVelocity - Character->GetActorLocation();
    float RelativeSpeed = FVector::DotProduct(RelativeVelocity, GetActorForwardVector());
    float ForceMagnitude = RelativeSpeed * RootPrimitive->GetMass() * CharacterImpactMultiplier;
    return ForceMagnitude;
}

void AVehicle::EngageHandbrake()
{
    HandbrakeEngaged = true;
    PlayBrakeSound(1.0f);
    if (DriverCharacter) 
    {
        DriverCharacter->Log("EngageHandbrake");
    }

}

void AVehicle::ReleaseHandbrake()
{
    HandbrakeEngaged = false;
    StopBrakeSound();
    if (DriverCharacter)
    {
        DriverCharacter->Log("ReleaseHandbrake");
    }
}

void AVehicle::UpdateHandbrake(float DeltaTime)
{
    if (HandbrakeEngaged)
    {
        FVector HandbrakeFrictionForce = -ForwardVelocity.GetSafeNormal() * HandbrakeFrictionCoefficient;
        RootPrimitive->AddForce(HandbrakeFrictionForce);
        FVector HandbrakeDragForce = CalculateDragForce(ForwardVelocity);
        RootPrimitive->AddForce(HandbrakeDragForce);
        HandbrakeRotationDamping = 2.0f;
        RollSpeed = FMath::FInterpTo(RollSpeed, 0.0f, DeltaTime, HandbrakeRotationDamping);
        HandbrakeSteeringDamping = 5.0f;
        SteeringAngle = FMath::FInterpTo(SteeringAngle, 0.0f, DeltaTime, HandbrakeSteeringDamping);
    }
}

void AVehicle::UpdateNOS(float DeltaTime)
{
    if (IsNOSActive)
    {
        NOSLoad -= NOSConsumption * DeltaTime;
        NOSLoad = FMath::Max(NOSLoad, 0.0f);
        FVector NOSForce = GetActorForwardVector() * NOSBoostStrength;
        VehicleMesh->AddForce(NOSForce);
        if (NOSLoad <= 0.0f) {
            NOSLoad = 0.0f;
            DeactivateNOS();
        }
    }
}

void AVehicle::ActivateNOS()
{
    if (NOSLoad > 0.0f)
    {
        IsNOSActive = true;
        PlayNOSSound(1.0f);
    }
    if (DriverCharacter)
    {
        DriverCharacter->Log("ActivateNOS");
    }
}

void AVehicle::DeactivateNOS()
{
    IsNOSActive = false;
    StopNOSSound();
    if (DriverCharacter)
    {
        DriverCharacter->Log("DeactivateNOS");
    }
}

void AVehicle::PlayEngineSound(float VolumeMultiplier)
{
    if (!EngineSoundComponent->IsPlaying())
    {
        EngineSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
        EngineSoundComponent->Play();
    }
}

void AVehicle::StopEngineSound()
{
    if (EngineSoundComponent->IsPlaying())
    {
        EngineSoundComponent->Stop();
    }
}

void AVehicle::PlayTireSkidSound(float VolumeMultiplier)
{
    if (!TireSkidSoundComponent->IsPlaying())
    {
        TireSkidSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
        TireSkidSoundComponent->Play();
    }
}

void AVehicle::StopTireSkidSound()
{
    if (TireSkidSoundComponent->IsPlaying())
    {
        TireSkidSoundComponent->Stop();
    }
}

void AVehicle::PlayBrakeSound(float VolumeMultiplier)
{
    if (!BrakeSoundComponent->IsPlaying())
    {
        BrakeSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
        BrakeSoundComponent->Play();
    }
}

void AVehicle::StopBrakeSound()
{
    if (BrakeSoundComponent->IsPlaying())
    {
        BrakeSoundComponent->Stop();
    }
}

void AVehicle::PlayThrottleSound(float VolumeMultiplier)
{
    if (ThrottleSoundComponent->IsPlaying())
    {
        ThrottleSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
        ThrottleSoundComponent->Play();
    }
}

void AVehicle::StopThrottleSound()
{
    if (ThrottleSoundComponent->IsPlaying())
    {
        ThrottleSoundComponent->Stop();
    }
}

void AVehicle::PlayNOSSound(float VolumeMultiplier)
{
    if (!NOSSoundComponent->IsPlaying())
    {
        NOSSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
        NOSSoundComponent->Play();
    }
}

void AVehicle::StopNOSSound()
{
    if (NOSSoundComponent->IsPlaying())
    {
        NOSSoundComponent->Stop();
    }
}

void AVehicle::PlayHitSound(float VolumeMultiplier)
{
    HitSoundComponent->SetVolumeMultiplier(VolumeMultiplier);
    HitSoundComponent->Play();
}

void AVehicle::StopHitSound()
{
    if (HitSoundComponent->IsPlaying())
    {
        HitSoundComponent->Stop();
    }
}

void AVehicle::ShowSpeechBuuble(FString Text, float FontSize, float Duration, AAdventureCharacter* TargetCharacter)
{
    if (GameMode) 
    {
        if (SpeechBubble) 
        {
            SpeechBubble->Hide();
        }
        SpeechBubble = GameMode->AddSpeechBubble(
            FText::FromString(Text),
            FontSize,
            Duration,
            new FVector(0.0f, -200.0f, 60.0f),
            new FRotator(0.0f, 90.0f, 0.0f),
            new FVector(1.0f, 1.0f, 1.0f),
            this,
            TargetCharacter,
            nullptr
        );
        if (SpeechBubble)
        {
            SpeechBubble->Vehicle = this;
        }
    }
}

FVector AVehicle::GetLookAtLocation()
{
    FVector NormalizedVelocity = ForwardVelocity;
    if (!NormalizedVelocity.Normalize())
    {
        NormalizedVelocity = GetActorForwardVector();
    }
    return GetActorLocation() + (NormalizedVelocity * LookAtLocation);
}