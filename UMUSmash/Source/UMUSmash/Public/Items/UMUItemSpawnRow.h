

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UMUItemSpawnRow.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FUMUItemSpawnRow :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;

};
