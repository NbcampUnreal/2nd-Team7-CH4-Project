

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FootStep")
	void TriggerFootStep();

	UFUNCTION(BlueprintCallable, Category = "FootStep")
	void ProcessDetectFeet(float AxisValue);


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
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* LaunchParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* CrouchParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* LedgeParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* DeadParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* ShieldParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* TumbleParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* ShieldTumbleParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* ProneParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* StunParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* DizzyParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* AbilityParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* DodgeParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* FreeFallParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* HeldParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* HoldParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep|Particle")
	UParticleSystem* DefaultParticle;


};






