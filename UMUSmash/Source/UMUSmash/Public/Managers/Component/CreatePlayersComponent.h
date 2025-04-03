

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatePlayersComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMUSMASH_API UCreatePlayersComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCreatePlayersComponent();

	void CreatePlayers();

	// getter & Setter
	TSoftClassPtr<UGameInstance> GetGameInstance() { return GameInstance_Comp; }
	int32 GetNumberOfPlayers() const { return NumberOfPlayers_Comp; }
	void SetNumberOfPlayers(const int32& NewValue) { NumberOfPlayers_Comp = NewValue; }
	int32 GetStocks() const { return Stocks_Comp; }
	void SetStocks(const int32& NewValue) { Stocks_Comp = NewValue; }
	int32 GetStockCount() const { return Stocks_Comp; }
	void SetStockCount(const int32& NewValue) { Stocks_Comp = NewValue; }
	int32 GetMinutes() const { return Minutes_Comp; }
	void SetMinutes(const int32& NewValue) { Minutes_Comp = NewValue; }
	


protected:
	TSoftClassPtr<UGameInstance> GameInstance_Comp;
	int32 NumberOfPlayers_Comp;
	int32 Stocks_Comp;
	int32 StockCount_Comp;
	int32 Minutes_Comp;
};
