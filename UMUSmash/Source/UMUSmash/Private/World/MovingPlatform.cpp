


#include "World/MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GlobalStartLocation + MoveOffset;
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector Target = bMovingToTarget ? GlobalTargetLocation : GlobalStartLocation;
    float Speed = MoveSpeed * DeltaTime;

    FVector Direction = (Target - CurrentLocation).GetSafeNormal();
    FVector NewLocation = CurrentLocation + Direction * Speed;

    SetActorLocation(NewLocation);

    if (FVector::Dist(NewLocation, Target) < 5.f)
    {
        bMovingToTarget = !bMovingToTarget;
    }
}

