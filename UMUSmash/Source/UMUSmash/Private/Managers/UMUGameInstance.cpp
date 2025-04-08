


#include "Managers/UMUGameInstance.h"

void UUMUGameInstance::ServerTravel(const FString& MapName) const
{
	GetWorld()->ServerTravel(MapName);
}