

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

UCLASS()
class UMUSMASH_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CallEndAbility();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool bIsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeLevel = 0.f;
};
