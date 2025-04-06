

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMU_FX_component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UUMU_FX_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUMU_FX_component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable) 
	void Fx_Main_Roop();
};
