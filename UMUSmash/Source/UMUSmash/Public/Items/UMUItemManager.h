

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UMUItemSpawner.h"
#include "UMUItemSpawnRow.h"
#include "UMUItemManager.generated.h"

/**
 * 
 */

UCLASS()
class UMUSMASH_API UUMUItemManager : public UWorldSubsystem
{
	GENERATED_BODY()
	


public:
	UUMUItemManager();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld);
	UFUNCTION()
	void AddSpawnerArray(AUMUItemSpawner* Spawner);
	UFUNCTION()
	void RoadItemData();
private:
	UFUNCTION(BlueprintCallable)
	void SelectSpawnerRun();
	
	UFUNCTION()
	FUMUItemSpawnRow SelectItem();

private: 
	UPROPERTY()
	UDataTable* ItemClassDataTable;

	UPROPERTY(VisibleAnywhere)
	TArray<FUMUItemSpawnRow> ItemArray;

	UPROPERTY(VisibleAnywhere)
	TArray<AUMUItemSpawner*> SpawnerArray;

	

};
