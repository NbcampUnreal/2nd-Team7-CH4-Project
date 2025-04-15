

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "UMUItemSpawner.generated.h"

UCLASS()
class UMUSMASH_API AUMUItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Niagara")
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Niagara")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* Scene;


	AUMUItemSpawner();
	



public:	
	// Called every frame
	UFUNCTION(BlueprintCallable)
	void SpawnItem(UClass* SpawnItem);

	UFUNCTION(BlueprintCallable)
	void CreateItem(UClass* Item);

	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	FTimerHandle TimerHandle;

};
