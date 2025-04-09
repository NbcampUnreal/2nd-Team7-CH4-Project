

#pragma once

#include "Character/BaseCharacter.h"
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
	UPROPERTY(EditAnyWhere)
	ABaseCharacter* Parent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void ScreenShake(float RumbleInten, float RumbleDuration);

		
};
