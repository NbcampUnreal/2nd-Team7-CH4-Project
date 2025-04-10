

#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockbackComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UKnockbackComponent : public UActorComponent
{
	GENERATED_BODY()
	//함수
public:	
	// Sets default values for this component's properties
	UKnockbackComponent();
	TObjectPtr<ABaseCharacter> Parent;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void CharacterKnockback(EInputDirection Direction, float Angle);
	float FuncNockbackCalculation();

	//변수
public:
protected:
private:
	bool bIsLaunched = false;
};
