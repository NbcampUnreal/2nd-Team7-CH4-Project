#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "DayNightController.generated.h"

UCLASS()
class UMUSMASH_API ADayNightController : public AActor
{
    GENERATED_BODY()

public:
    ADayNightController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    void InitializeLights();

    ADirectionalLight* DirectionalLightActor = nullptr;
    ASkyLight* SkyLightActor = nullptr;

    float CurrentTime = 0.0f;

public:
    UPROPERTY(EditAnywhere, Category = "DayNight")
    float TimeSpeed = 1.0f / 30.0f;

    UPROPERTY(EditAnywhere, Category = "DayNight")
    float StartPitch = 10.0f;

    UPROPERTY(EditAnywhere, Category = "DayNight")
    float EndPitch = -90.0f;

    UPROPERTY(EditAnywhere, Category = "DayNight")
    float DayIntensity = 10.0f;

    UPROPERTY(EditAnywhere, Category = "DayNight")
    float NightIntensity = 0.0f;

    UPROPERTY(EditAnywhere, Category = "DayNight")
    FLinearColor DayLightColor = FLinearColor(1.0f, 0.95f, 0.85f);

    UPROPERTY(EditAnywhere, Category = "DayNight")
    FLinearColor NightLightColor = FLinearColor(0.2f, 0.25f, 0.35f);
};
