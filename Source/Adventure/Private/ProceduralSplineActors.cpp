
#include "ProceduralSplineActors.h"


AProceduralSplineActors::AProceduralSplineActors()
{
	PrimaryActorTick.bCanEverTick = true;

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    Spline->SetupAttachment(RootComponent);

}

void AProceduralSplineActors::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    InitOrUpdateSplineChanges();
}

void AProceduralSplineActors::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AProceduralSplineActors, Spline))
    {
        InitOrUpdateSplineChanges();
    }
}

void AProceduralSplineActors::BeginPlay()
{
	Super::BeginPlay();
    InitOrUpdateSplineChanges();
}

void AProceduralSplineActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateSpline(DeltaTime);
    UpdateActors(DeltaTime);
}

void AProceduralSplineActors::SetSplineComponent(class USplineComponent* SplineToFollow)
{
    if (SplineToFollow != Spline)
    {
        Spline = SplineToFollow;
        InitOrUpdateSplineChanges();
    }
}


void AProceduralSplineActors::InitOrUpdateSplineChanges()
{
    if (SplineType != SelectedSplineType)
    {
        SelectedSplineType = SplineType;
        CreateSpline();
    }
    CreateObjects();

}


void AProceduralSplineActors::CreateSpline()
{
    switch (SplineType)
    {
    case EProceduralSplineType::Line:
        CreateLineSpline(FVector(0.0,0.0,0.0), FVector(1000.0, 0.0, 0.0), NumSplinePoints);
        break;

    case EProceduralSplineType::Disc:
        CreateDiscSpline(500.0f, NumSplinePoints);
        break;

    default:
        // Handle unexpected cases
        break;
    }
}

void AProceduralSplineActors::CreateLineSpline(FVector PointA, FVector PointB, int32 Points)
{
    if (Spline && Points > 1)
    {
        Spline->ClearSplinePoints(false);

        for (int32 i = 0; i < Points; ++i)
        {
            float T = static_cast<float>(i) / (Points - 1); // Normalized value between 0 and 1
            FVector PointLocation = FMath::Lerp(PointA, PointB, T);

            Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::Local, true);
        }

        Spline->UpdateSpline();
    }
}

void AProceduralSplineActors::CreateDiscSpline(float Radius, int32 Points)
{
    if (Spline)
    {
        Spline->ClearSplinePoints(false);

        const float DeltaAngle = 360.0f / static_cast<float>(Points);
        for (int32 i = 0; i < Points; ++i)
        {
            const float Angle = DeltaAngle * i;
            const float RadAngle = FMath::DegreesToRadians(Angle);
            const FVector PointLocation = FVector(FMath::Cos(RadAngle) * Radius, FMath::Sin(RadAngle) * Radius, 0.0f);

            Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::Local, true);
        }

        Spline->SetClosedLoop(true, true);
        Spline->UpdateSpline();
    }
}


void AProceduralSplineActors::ClearObjects()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("ClearObjects"));
    }
    for (AActor* ObjectToDestroy : CreatedActors)
    {
        if (ObjectToDestroy)
        {
            ObjectToDestroy->Destroy();
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, ObjectToDestroy->GetName());
            }
        }

    }
    CreatedActors.Empty();
}

void AProceduralSplineActors::CreateObjects()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("CreateObjects"));
    }
    ClearObjects();
    if (ActorClass && Spline)
    {
        const float SplineLength = Spline->GetSplineLength();
        const float DistanceBetweenInstances = SplineLength / NumObjectsToCreate;

        for (int32 InstanceIndex = 0; InstanceIndex < NumObjectsToCreate; ++InstanceIndex)
        {
            const float ObjectDistanceAlongSpline = DistanceBetweenInstances * InstanceIndex * ObjectDistanceAlongSplineFactor;

            AActor* NewInstance = GetWorld()->SpawnActor<AActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
            if (NewInstance)
            {
                FVector Location = Spline->GetLocationAtDistanceAlongSpline(ObjectDistanceAlongSpline, ESplineCoordinateSpace::World);
                FVector Tangent = Spline->GetTangentAtDistanceAlongSpline(ObjectDistanceAlongSpline, ESplineCoordinateSpace::World);

                NewInstance->SetActorLocation(Location);
                NewInstance->SetActorRotation(Tangent.Rotation());

                CreatedActors.Add(NewInstance);
            }
        }
    }
}


void AProceduralSplineActors::UpdateSpline(float DeltaTime)
{
    if (Spline)
    {
    }
}

void AProceduralSplineActors::UpdateActors(float DeltaTime)
{
}