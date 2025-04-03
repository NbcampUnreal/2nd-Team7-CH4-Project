

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h" // EPhysicalSurface 사용을 위한 헤더
#include "Sound/SoundBase.h"
#include "FootStepComp.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UMUSMASH_API UFootStepComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootStepComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	FVector FootLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	USoundBase* FootPrintSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	USoundBase* FootPrintFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	float Volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FootStep")
	int32 SurfaceNo;
};
