

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightController.generated.h"

UCLASS()
class UMUSMASH_API ADayNightController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
