

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

class ABaseCharacter;

UCLASS()
class UMUSMASH_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CallEndAbility();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ABaseCharacter> BaseCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bIsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeLevel = 0.f;
};
