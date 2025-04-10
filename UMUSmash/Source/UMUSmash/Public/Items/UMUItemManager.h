

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

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void AddSpawnerArray(AUMUItemSpawner* Spawner);

private:
	UFUNCTION()
	void SelectSpawner();
	
	UFUNCTION()
	FUMUItemSpawnRow SelectItem();
private: 

	UPROPERTY(VisibleAnywhere)
	TArray<FUMUItemSpawnRow> ItemArray;
	UPROPERTY(VisibleAnywhere)
	TArray<AUMUItemSpawner*> SpawnerArray;

	

};
