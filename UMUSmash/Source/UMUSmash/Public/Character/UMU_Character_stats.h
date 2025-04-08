

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMU_Character_stats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UUMU_Character_stats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUMU_Character_stats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
