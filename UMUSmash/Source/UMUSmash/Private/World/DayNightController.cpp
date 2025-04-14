


#include "World/DayNightController.h"
#include "Components/LightComponent.h"
#include "Components/SkyLightComponent.h"

ADayNightController::ADayNightController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADayNightController::BeginPlay()
{
    Super::BeginPlay();
    InitializeLights();
}

void ADayNightController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!DirectionalLightActor) return;

    CurrentTime += DeltaTime * TimeSpeed;
    if (CurrentTime > 1.0f)
    {
        CurrentTime = 0.0f;
    }

    float NewPitch = FMath::Lerp(StartPitch, EndPitch, CurrentTime);
    DirectionalLightActor->SetActorRotation(FRotator(NewPitch, 0, 0));

    float NewIntensity = FMath::Lerp(DayIntensity, NightIntensity, CurrentTime);
    DirectionalLightActor->GetLightComponent()->SetIntensity(NewIntensity);

    FLinearColor NewColor = FMath::Lerp(DayLightColor, NightLightColor, CurrentTime);
    DirectionalLightActor->SetLightColor(NewColor);

    if (SkyLightActor)
    {
        SkyLightActor->GetLightComponent()->MarkRenderStateDirty();
    }
}

void ADayNightController::InitializeLights()
{
    for (TActorIterator<ADirectionalLight> It(GetWorld()); It; ++It)
    {
        DirectionalLightActor = *It;
        break;
    }

    for (TActorIterator<ASkyLight> It(GetWorld()); It; ++It)
    {
        SkyLightActor = *It;
        break;
    }
}


