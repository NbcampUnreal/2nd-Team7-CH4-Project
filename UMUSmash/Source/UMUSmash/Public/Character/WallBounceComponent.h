

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallBounceComponent.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UWallBounceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallBounceComponent();
	UFUNCTION(BlueprintCallable)
	void WallBounce();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	void WallBouceCalc();
public:	

	TObjectPtr<ABaseCharacter> Parent = nullptr;
protected:

private:
	FTimerHandle DelayTimer;
	FTimerHandle WallBounceDelayTimer;
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
		
};
