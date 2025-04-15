
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UMUSMASH_API AMovingPlatform : public AActor
{
    GENERATED_BODY()

public:
    AMovingPlatform();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    FVector GlobalStartLocation;
    FVector GlobalTargetLocation;

    //true∏È A°ÊB false∏È B°ÊA
    bool bMovingToTarget = true;

public:
    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector MoveOffset = FVector(1000, 0, 0);

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 200.0f;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlatformMesh;
};
