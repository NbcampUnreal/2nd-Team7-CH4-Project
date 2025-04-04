#pragma once

#include "UMUTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbility();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void MainTick();
	UFUNCTION(BlueprintCallable)
	void SwitchOnAbilityType();
	UFUNCTION(BlueprintCallable)
	void BasicAttack();
	UFUNCTION(BlueprintCallable)
	void SpecialAttack();
	UFUNCTION(BlueprintCallable)
	void AirAttack();
	UFUNCTION(BlueprintCallable)
	void SmashAttack();
	UFUNCTION(BlueprintCallable)
	void Dodge();
	UFUNCTION(BlueprintCallable)
	void Taunt();
	UFUNCTION(BlueprintCallable)
	void Throw();
	UFUNCTION(BlueprintCallable)
	void Prone();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ABaseCharacter> Parent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputDirection DirectionType = EInputDirection::None;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
