

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LedgeComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API ULedgeComponent : public UActorComponent
{
	GENERATED_BODY()
	//함수
public:	
	// Sets default values for this component's properties
	ULedgeComponent();
	UFUNCTION(BlueprintCallable, Category = "LedgeComponent")
	void LedgeGrab();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:

	// 변수
public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	TObjectPtr<ABaseCharacter> Parent = nullptr;	
protected:
private:
	FTimerHandle LedgeGrabTimer;
};
