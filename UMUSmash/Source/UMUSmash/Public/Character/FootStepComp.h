#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "UMUTypes.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "FootStepComp.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UMUSMASH_API UFootStepComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootStepComp();

private:

	TMap<FName, bool> LocalTriggerMap;

	UFUNCTION()
	TEnumAsByte<EPhysicalSurface> GetSurfaceType(const FHitResult& Hit) const;

	UPROPERTY(EditDefaultsOnly, Category = "Footstep")
	float TraceDistance = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Footstep")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	bool PerformFootTrace(FHitResult& OutHit, FVector Start, FVector End);

public:

	UFUNCTION(BlueprintCallable, Category = "FootStep")
	void TriggerFootStep();

	UFUNCTION(BlueprintCallable, Category = "FootStep")
	void ProcessDualFeet(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "FootStep")
	void ProcessDetectFoot(FName InSocketName, float AxisValue);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	FVector FootLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	TArray<USoundBase*> FootPrintSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	TArray<UForceFeedbackEffect*> FootPrintFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	float Volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	int32 SurfaceNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	EPlayerStateType CurrentPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* IdleParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* WalkRunParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* SprintParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* JumpParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* FallParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* DefaultParticle;


};