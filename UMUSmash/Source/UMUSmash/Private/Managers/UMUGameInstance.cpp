


#include "Managers/UMUGameInstance.h"

void UUMUGameInstance::OpenLevel(const FString& MapName) const
{
	UWorld* World = GetWorld();
	check(World);

	World->ServerTravel(MapName);
}

void UUMUGameInstance::ServerTravel_Implementation(const FString& MapName)
{
	OpenLevel(MapName);
	MulticastRPCClientsTravel(MapName);
}

void UUMUGameInstance::MulticastRPCClientsTravel_Implementation(const FString& MapName)
{
	OpenLevel(MapName);
}
