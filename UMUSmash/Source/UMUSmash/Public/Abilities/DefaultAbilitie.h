

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultAbilitie.generated.h"

UCLASS()
class UMUSMASH_API ADefaultAbilitie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultAbilitie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
