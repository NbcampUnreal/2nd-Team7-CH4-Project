#include "Character/FootStepComp.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

UFootStepComp::UFootStepComp()
{
    PrimaryComponentTick.bCanEverTick = true;
    TraceDistance = 20.0f;
    TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
}

void UFootStepComp::ProcessDualFeet(float AxisValue)
{
    const float AbsAxisValue = FMath::Abs(AxisValue);

    ProcessDetectFoot(FName("foot_lSocket"), AbsAxisValue);
    ProcessDetectFoot(FName("foot_rSocket"), AbsAxisValue);
}

void UFootStepComp::ProcessDetectFoot(FName InSocketName, float AxisValue) //
{
    if (!GetOwner() || !GetWorld()) return;

    const float Threshold = 0.2f;

    bool& bCanTrigger = LocalTriggerMap.FindOrAdd(InSocketName, true);

    if (AxisValue < Threshold)
    {
        bCanTrigger = true;
        return;
    }

    if (bCanTrigger)
    {
        if (USkeletalMeshComponent* MeshComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
        {
            FVector Start = MeshComp->GetSocketLocation(InSocketName);
            FVector End = Start + FVector(0, 0, -TraceDistance);

            FHitResult Hit;
            if (PerformFootTrace(Hit, Start, End))
            {
                FootLocation = Hit.ImpactPoint;
                SurfaceType = GetSurfaceType(Hit);
                TriggerFootStep();
                bCanTrigger = false;
            }
        }
    }
}

bool UFootStepComp::PerformFootTrace(FHitResult& OutHit, FVector Start, FVector End)
{
    if (!GetWorld()) return false;

    FCollisionQueryParams Params;
    Params.bReturnPhysicalMaterial = true;
    Params.AddIgnoredActor(GetOwner());

    ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);
    // fixed with copilot
    return GetWorld()->LineTraceSingleByChannel(
        OutHit,
        Start,
        End,
        CollisionChannel,
        Params
    );
}

TEnumAsByte<EPhysicalSurface> UFootStepComp::GetSurfaceType(const FHitResult& Hit) const
{
    return Hit.PhysMaterial.IsValid() ?
        UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get()) :
        SurfaceType_Default;
}


void UFootStepComp::TriggerFootStep()
{
    if (FootPrintSounds.Num() > 0 && FootPrintSounds[0])
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            FootPrintSounds[0],
            FootLocation,
            Volume
        );
    }

    UParticleSystem* SelectedParticle = DefaultParticle;

    if (CurrentPlayerState == EPlayerStateType::Idle)
    {
        SelectedParticle = IdleParticle;
    }
    else if (CurrentPlayerState == EPlayerStateType::walkrun)
    {
        SelectedParticle = WalkRunParticle;
    }
    else if (CurrentPlayerState == EPlayerStateType::sprint)
    {
        SelectedParticle = SprintParticle;
    }
    else if (CurrentPlayerState == EPlayerStateType::jump)
    {
        SelectedParticle = JumpParticle;
    }
    if (SelectedParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            SelectedParticle,
            FootLocation
        );
    }
}