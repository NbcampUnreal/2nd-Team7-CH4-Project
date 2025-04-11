

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockbackComponent.generated.h"

class ABaseCharacter;
class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UKnockbackComponent : public UActorComponent
{
	GENERATED_BODY()
	//함수
public:	
	// Sets default values for this component's properties
	UKnockbackComponent();
	TObjectPtr<ABaseCharacter> Parent;
	UFUNCTION(BlueprintCallable)
	void CharacterKnockback(EFaceDirection Direction, float Angle, float Stun);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float FuncNockbackCalculation();
	void LaunchBounce(FVector LaunchVector);
	//변수
public:
protected:
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> ParentCapsuleComp;

	UPROPERTY(EditAnywhere)
	float LaunchThreshold = 1000.f;

	bool bIsLaunched = false;

	FTimerHandle KnockbackDelayTimer;
};
