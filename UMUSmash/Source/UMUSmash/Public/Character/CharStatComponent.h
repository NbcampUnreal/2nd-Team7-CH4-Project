#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharStatComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UCharStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharStatComponent();
	UFUNCTION(BlueprintCallable)
	void ScreenShake(float RumbleInten, float RumbleDuration);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Dam);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Life", Replicated)
	int32 HP;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Life", Replicated)
	int32 MaxHP;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Life", Replicated)
	int32 Percent;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Life", Replicated)
	int32 Stock;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 SuperGage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	double DefaultGravityScale = 1.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	double Weight = 1.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Elims = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 DamageDone = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 DamageTaken = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Falls = 0;
protected:
	UPROPERTY(EditAnyWhere)
	TObjectPtr<ABaseCharacter> Parent;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> ShakeClass;

};


