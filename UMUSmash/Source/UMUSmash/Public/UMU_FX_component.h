

#pragma once

#include "Character/BaseCharacter.h"
#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMU_FX_component.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UUMU_FX_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUMU_FX_component();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable) 
	void Fx_Main_Roop();

	UPROPERTY(EditAnyWhere)
	ABaseCharacter *Parent;
	UPROPERTY(EditAnyWhere)
	UParticleSystemComponent* Smoke;
	UParticleSystem* P_SmokeTrail;
	bool Do_Once;

};
