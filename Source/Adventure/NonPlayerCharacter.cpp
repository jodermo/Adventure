#include "NonPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "NavigationSystem.h" 
#include "NavigationPath.h"

ANonPlayerCharacter::ANonPlayerCharacter() 
{
    FieldOfViewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldOfViewMesh"));
    FieldOfViewMesh->SetupAttachment(RootComponent);
    FieldOfViewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    FieldOfViewMesh->SetRelativeLocation(EyesLocation);
    ProceduralFieldOfViewMesh = CreateDefaultSubobject<UCustomProceduralMeshComponent>(TEXT("ProceduralFieldOfViewMesh"));
    ProceduralFieldOfViewMesh->SetupAttachment(FieldOfViewMesh);
    ProceduralFieldOfViewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANonPlayerCharacter::InitCharacter()
{
    Super::InitCharacter();
    FieldOfViewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ProceduralFieldOfViewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    MovementComponent->bUseControllerDesiredRotation = true;
    MovementComponent->bOrientRotationToMovement = true;
    UpdateLookAround(0);
    DoCaptureFace = true;
}

void ANonPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!IsDead)
    {
        UpdateLookAround(DeltaSeconds);
        if (!IsThrown)
        {
            UpdateMoveToCharacter(DeltaSeconds);
            UpdateMoveToTarget(DeltaSeconds);
        }
        UpdateFieldOfViewMesh(DeltaSeconds);
    }
}

void ANonPlayerCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
    AAdventureCharacter* OtherCharacter = Cast<AAdventureCharacter>(Other);

    if (MoveAround && !IsLookingAtCharacter)
    {
        MoveToRandomLocationInRadius(MoveAroundRadius);
    }
    if (StepBackIfToClose && OtherCharacter && OtherCharacter->AttractNPC && !OtherCharacter->Hidden && !IgnoreCharacters.Contains(OtherCharacter))
    {
        FVector DirectionToPlayer = OtherCharacter->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Normalize();
        FVector NewPosition = GetActorLocation() - (DirectionToPlayer * StepBackDistance);
        FVector StepBackDirection = -DirectionToPlayer;
        FRotator NewRotation = DirectionToPlayer.Rotation();
        SetActorRotation(NewRotation);
        UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
        MovementComponent->MaxWalkSpeed = WalkSpeed;
        AddMovementInput(StepBackDirection, StepBackAmount);
    }
}

void ANonPlayerCharacter::Die()
{
    Super::Die();
    HideFieldOfViewMesh();
}

void ANonPlayerCharacter::SetCurrentMovementSpeed(float NewSpeed)
{
    CurrentMovementSpeed = NewSpeed;
}

float ANonPlayerCharacter::CalculateRecognitionDistance(AAdventureCharacter* Character) {
    float CharacterRecognitionDistance = MaxRecognitionDistance;
    CharacterRecognitionDistance = CharacterRecognitionDistance * Attention;
    CharacterRecognitionDistance = CharacterRecognitionDistance - (Character->IsCrouching ? Character->ReduceRecognitionDistanceCrouching : 0);
    CharacterRecognitionDistance = CharacterRecognitionDistance + (!Character->IsCrouching && Character->IsSprinting ? Character->AddRecognitionDistanceSprinting : 0);
    CharacterRecognitionDistance = CharacterRecognitionDistance * Character->Conspicuousness;
    CharacterRecognitionDistance = CharacterRecognitionDistance - (RecognitionDistance * Character->Concealment);
    return CharacterRecognitionDistance;
}

void ANonPlayerCharacter::ClearTarget()
{
    SteppingBack = false;
    TargetIsWithinSprintDistance = false;
    TargetDistance = 0.0f;
    TargetAngle = 0.0f;
}

bool ANonPlayerCharacter::IsBestTarget(AAdventureCharacter* Character)
{
    bool IsBest = true;
    if (Character == this || !Character->AttractNPC || Character->Hidden || IgnoreCharacters.Contains(Character)) {
        IsBest = false;
    }
    if (IsBest && TargetCharacter && !(PreferPlayerCharacter && Character->IsPlayer))
    {
        IsBest =(Character->Conspicuousness - Character->Concealment) > (TargetCharacter->Conspicuousness - TargetCharacter->Concealment);
    }
    return IsBest;
}

bool ANonPlayerCharacter::IsCharacterInViewField(AAdventureCharacter* Character, float CharacterRecognitionDistance)
{
    if (!Character)
    {
        return false;
    }
    FVector CharactertLocation = Character->GetActorLocation();
    FVector DirectionToCharacter = CharactertLocation - GetActorLocation();
    float DistanceToCharacter = DirectionToCharacter.Size();;
    DirectionToCharacter.Normalize();
    float AngleToTarget = FMath::Acos(FVector::DotProduct(DirectionToCharacter, GetActorForwardVector())) * (180.0f / PI);
    bool IsInFOV = AngleToTarget <= FieldOfViewAngle * 0.5f;
    if (DistanceToCharacter > CharacterRecognitionDistance) {
        IsInFOV = false;
    }
    if (IsInFOV)
    {
        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        FVector TraceStart = GetActorLocation() + EyesLocation + EyeTraceStartOffset;
        bool LookingAtObject = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, CharactertLocation, ECC_Visibility, CollisionParams);
        AActor* LookAtActor = HitResult.GetActor();
        if ((!LookingAtObject && LookAtActor != this) || LookAtActor == Character)
        {
            return true;
        }
    }
    return false;
}

void ANonPlayerCharacter::UpdateLookAround(float DeltaSeconds)
{
    if (GameMode)
    {
        IsLookingAtCharacter = false;
        if (IsLookingAround)
        {
            TargetCharacter = nullptr;
            float FinalRecognitionDistance = PlayerCharacter ? CalculateRecognitionDistance(PlayerCharacter) : MaxRecognitionDistance;
            if (CanDetectCharacters)
            {
                for (AAdventureCharacter* Character : GameMode->Characters)
                {
                    if (!IgnoreCharacters.Contains(Character)) {
                        if (IsCharacterInViewField(Character, FinalRecognitionDistance) && IsBestTarget(Character))
                        {
                            float CharacterRecognitionDistance = CalculateRecognitionDistance(Character);
                            float Distance = FVector::Distance(Character->GetActorLocation(), GetActorLocation());

                            if (!IsLookingAtCharacter || Distance < CharacterRecognitionDistance)
                            {

                                IsLookingAtCharacter = true;
                                TargetIsWithinSprintDistance = Distance >= SprintingDistance;
                                TargetCharacter = Character;
                                SteppingBack = Distance > StepBackDistance;
                                FinalRecognitionDistance = CharacterRecognitionDistance;
                                MoveToLocation(Character->GetActorLocation());
                            }
                        }
                    }
                }
            }
            if (!IsLookingAtCharacter)
            {
                if (LookAroundTime >= LookAroundDuration)
                {
                    TargetLookDirection = FRotator(0.0f, FMath::RandRange(-180.0f, 180.0f), 0.0f);
                    LookAroundTime = 0.0f;
                }
                else
                {
                    LookAroundTime += DeltaSeconds;
                }
                FRotator CurrentRotation = GetActorRotation();
                FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetLookDirection, DeltaSeconds, LookAroundSpeed);
                SetActorRotation(NewRotation);
            }
            if (FinalRecognitionDistance != RecognitionDistance)
            {
                RecognitionDistance = FinalRecognitionDistance;
                if (UseFieldOfViewMesh) 
                {
                    GenerateProceduralFieldOfViewMesh(FieldOfViewAngle, RecognitionDistance, 16, RecognitionDistance);
                }
            }
        }
        if (!IsLookingAround && IsMovingAround)
        {
            FVector TraceStart = GetActorLocation();
            FVector TraceEnd = GetActorLocation() + GetActorRotation().Vector() * MaxLookAroundDistance;
            FHitResult HitResult;
            FCollisionQueryParams CollisionParams;
            bool bHitObstacle = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
            if (bHitObstacle)
            {
                TargetLookDirection = TargetLookDirection * -1;
            }
            IsLookingAround = true;
        }
        if (!IsLookingAtCharacter && !IsMovingAround && MoveAround)
        {
            MoveToRandomLocationInRadius(MoveAroundRadius);
        }
    }
}

void ANonPlayerCharacter::UpdateMoveToCharacter(float DeltaSeconds)
{
    if (TargetCharacter)
    {
        TargetDistance = FVector::Distance(TargetCharacter->GetActorLocation(), GetActorLocation());
    }
    if (!IsThrown && CanDetectCharacters && IsLookingAtCharacter && TargetCharacter)
    {
        if (TargetDistance > StepBackDistance)
        {
            if (TargetIsWithinSprintDistance && !SteppingBack)
            {
                StartSprint();
            }
            else
            {
                if (SteppingBack && StepBackValue <= 0.0f)
                {
                    StepBackValue = StepBackAmount;
                }
                else
                {
                    SteppingBack = false;
                }
                StopSprint();
            }
            if (!TargetCharacter->FollowingCharacters.Contains(this))
            {
                TargetCharacter->FollowingCharacters.Add(this);
            }
            MoveToLocation(TargetCharacter->GetActorLocation());
        }
        else
        {
            SteppingBack = true;
            FVector TargetPosition = GetActorLocation() - (GetActorForwardVector() * StepBackDistance);
            FVector NewPosition = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaSeconds, StepBackSpeed);
            SetActorLocation(NewPosition);
        }
    }
    if (!IsThrown && !IsLookingAtCharacter && TargetCharacter && TargetCharacter != this && TargetCharacter->FollowingCharacters.Contains(this))
    {
        TargetCharacter->FollowingCharacters.Remove(this);
    }
}

void ANonPlayerCharacter::IgnoreCharacter(AAdventureCharacter* CharacterToIgnore)
{
    Super::IgnoreCharacter(CharacterToIgnore);
    if (TargetCharacter == CharacterToIgnore) 
    {
        if (TargetCharacter)
        {
            if (TargetCharacter->FollowingCharacters.Contains(this))
            {
                TargetCharacter->FollowingCharacters.Remove(this);
            }
        }
        TargetCharacter = nullptr;
        IsLookingAtCharacter = false;
    }
}

void ANonPlayerCharacter::UpdateMoveToTarget(float DeltaSeconds)
{
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    bool HasMoved = false;
    if (!IsThrown && IsLookingAtCharacter && TargetCharacter && TargetDistance <= MaxTargetDistance)
    {
        DoCharacterInteraction(TargetCharacter, DeltaSeconds);
        return;
    }
    if (IsMovingAround && NavSystem)
    {
        DistanceToTarget = FVector::Distance(TargetLocation, GetActorLocation());
        UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(this, GetActorLocation(), TargetLocation, this, TSubclassOf<UNavigationQueryFilter>());
        if (NavPath && NavPath->IsValid())
        {
            PathPoints = NavPath->PathPoints;
            while (PathPoints.Num() > 0)
            {
                FVector CurrentTarget = PathPoints[0];
                FVector Direction = CurrentTarget - GetActorLocation();
                Direction.Normalize();
                if (SteppingBack && StepBackValue >= 0.0f)
                {
                    if (StepBackValue > 0.0f) {
                        StepBackValue -= DeltaSeconds;
                    }
                    else {
                        StepBackValue = 0.0f;
                        SteppingBack = false;
                    }
                }
                else {
                    SteppingBack = false;
                    MoveDirection(Direction, DeltaSeconds);
                    HasMoved = true;
                }
                if (FVector::DistSquaredXY(GetActorLocation(), CurrentTarget) < FMath::Square(50.0f))
                {
                    PathPoints.RemoveAt(0);
                }
                else
                {
                    break;
                }
            }
        }
    }
    if (!IsThrown && IsMovingAround && !SteppingBack && PathPoints.Num() == 0)
    {
        FVector CurrentLocation = GetActorLocation();
        if (FVector::DistSquaredXY(CurrentLocation, TargetLocation) < FMath::Square(50.0f))
        {
            StopSprint();
            StopMoving();
            IsMovingAround = false;
            if (MoveAround && !IsLookingAtCharacter)
            {
                MoveToRandomLocationInRadius(MoveAroundRadius);
            }
        }
    }
}

void ANonPlayerCharacter::UpdateFieldOfViewMesh(float DeltaSeconds)
{
    if (!IsDead && FieldOfViewMesh && UseFieldOfViewMesh)
    {
        FVector ForwardVector = GetActorForwardVector();
        FRotator MeshRotation = ForwardVector.Rotation();
        FVector RotatedForwardVector = GetActorRotation().RotateVector(GetActorForwardVector());
        FVector ConeOffset = FVector(0.0f, 0.0f, 0.0f);
        FieldOfViewMesh->SetWorldLocation(GetActorLocation());
        FieldOfViewMesh->SetRelativeLocation(EyesLocation + ConeOffset);
        FieldOfViewMesh->SetWorldRotation(MeshRotation + FRotator(-90.0f, 0.0f, 0.0f));
        if (ProceduralFieldOfViewMesh) {
            if (IsLookingAtCharacter)
            {
                if (FieldOfViewRecognitionMaterial)
                {
                    ProceduralFieldOfViewMesh->SetMaterial(0, FieldOfViewRecognitionMaterial);
                }
                else  if (FieldOfViewMaterial)
                {
                    ProceduralFieldOfViewMesh->SetMaterial(0, FieldOfViewMaterial);
                }
            }
            else
            {
                if (FieldOfViewMaterial)
                {
                    ProceduralFieldOfViewMesh->SetMaterial(0, FieldOfViewMaterial);
                }
            }
        }
        ShowFieldOfViewMesh();
    }
    else
    {
        HideFieldOfViewMesh();
    }
}

void ANonPlayerCharacter::ShowFieldOfViewMesh()
{
    if (UseFieldOfViewMesh && !IsDead) 
    {
        FieldOfViewMesh->SetVisibility(true, true);
        ProceduralFieldOfViewMesh->SetVisibility(true, true);
    }
    else
    {
        HideFieldOfViewMesh();
    }
}

void ANonPlayerCharacter::HideFieldOfViewMesh()
{
    FieldOfViewMesh->SetVisibility(false, true);
    ProceduralFieldOfViewMesh->SetVisibility(false, true);
}

void ANonPlayerCharacter::GenerateProceduralFieldOfViewMesh(float ConeAngle, float ConeHeight, int32 NumSides, float ConeRadius)
{
    if (UseFieldOfViewMesh) {
        ProceduralFieldOfViewMesh->ClearAllMeshSections();
        TArray<FVector> Vertices;
        TArray<int32> Triangles;
        FVector ConeApex = FVector(0.0f, 0.0f, 0.0f);
        Vertices.Add(ConeApex);
        for (int32 i = 0; i < NumSides; ++i)
        {
            float Angle = 2 * PI * i / NumSides;
            FVector VertexPosition = FVector(FMath::Cos(Angle) * ConeRadius, FMath::Sin(Angle) * ConeRadius, ConeHeight);
            Vertices.Add(VertexPosition);

            if (i < NumSides - 1)
            {
                Triangles.Add(0);
                Triangles.Add(i + 1);
                Triangles.Add(i + 2);
            }
            else
            {
                Triangles.Add(0); 
                Triangles.Add(i + 1);
                Triangles.Add(1);
            }
        }

        TArray<FVector> VerticesCopy = Vertices; 

        for (int32 i = 0; i < NumSides; ++i)
        {
            float Angle = 2 * PI * i / NumSides;
            FVector VertexPosition = FVector(FMath::Cos(Angle) * ConeRadius, FMath::Sin(Angle) * ConeRadius, ConeHeight);
            Vertices.Add(VertexPosition);

            if (i < NumSides - 1)
            {
                Triangles.Add(0);
                Triangles.Add(i + 1);
                Triangles.Add(i + 2);
            }
            else
            {
                Triangles.Add(0);
                Triangles.Add(i + 1);
                Triangles.Add(1);
            }
        }
        ProceduralFieldOfViewMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
        FQuat RotationQuat = FQuat(FRotator(-90.0f, 0.0f, 0.0f));
        FVector RotatedForwardVector = GetActorRotation().RotateVector(GetActorForwardVector());


        ProceduralFieldOfViewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ANonPlayerCharacter::MoveToLocation(FVector NewTargetLocation)
{
    ClearTarget();
    TargetDirection = NewTargetLocation - GetActorLocation();
    TargetAngle = FMath::Acos(FVector::DotProduct(TargetDirection, GetActorForwardVector())) * (180.0f / PI);
    TargetLocation = NewTargetLocation;
    TargetDistance = FVector::Distance(TargetLocation, GetActorLocation());
    IsMovingAround = true;
}

FVector ANonPlayerCharacter::GenerateRandomLocationInRadius(float MoveRadius)
{
    FVector2D RandomLocation2D = FMath::RandPointInCircle(MoveRadius);
    FVector RandomLocation(RandomLocation2D.X, RandomLocation2D.Y, 0.0f); // GetActorLocation().Z
    RandomLocation += GetActorLocation();
    return RandomLocation;
}

void ANonPlayerCharacter::MoveToRandomLocationInRadius(float MoveRadius)
{
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSystem)
    {
        return;
    }
    FVector RandomLocation;
    FVector Origin = GetActorLocation();
    FNavLocation NavLocation;
    if (NavSystem->GetRandomPointInNavigableRadius(Origin, MoveRadius, NavLocation))
    {
        RandomLocation = NavLocation.Location;
        MoveToLocation(RandomLocation);
    }
    else
    {
        FTimerHandle MoveRetryTimerHandle;
        GetWorldTimerManager().SetTimer(MoveRetryTimerHandle, this, &ANonPlayerCharacter::RetryMoveToRandomLocation, RetryMoveToRandomLocationDelay, false);
    }
}

void ANonPlayerCharacter::RetryMoveToRandomLocation()
{
    MoveToRandomLocationInRadius(MoveAroundRadius);
}

AVehicle* ANonPlayerCharacter::GetClosestVehicle()
{
    AVehicle* Vehicle = Super::GetClosestVehicle();
    if (NearVehicle && Vehicle  && Vehicle->DriverCharacter && Vehicle->IsMoving)
    {
        SetPhysicsOnly(true);
    }
    else {
        SetPhysicsOnly(false);
    }
    return Vehicle;
}

bool ANonPlayerCharacter::CanAttackCharacter(AAdventureCharacter* Character)
{
    if (Character)
    {
        return true;
    }
    return false;
}
