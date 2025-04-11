#include "Managers/UMUGameInstance.h"
#include "Managers/UMUFightGameMode.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Managers/UMUGameState.h"
#include "UMUSmash/UMUSmash.h"

void UUMUGameInstance::ServerTravel(const FString& MapName) const
{
	GetWorld()->ServerTravel(MapName);
}

bool UUMUGameInstance::IsGameOver() const
{
	return bIsGameOver;
}

void UUMUGameInstance::SetIsGameOver(const bool& NewValue)
{
	bIsGameOver = NewValue;
	GetWorld()->GetGameState<AUMUGameState>()->UpdateIsGameOver();
}

void UUMUGameInstance::CheckGameOverConditions()
{
	auto* FighterGameMode = Cast<AUMUFightGameMode>(GetWorld()->GetAuthGameMode());
	checkf(FighterGameMode, TEXT("Game Instance: Fighter Game Mode is null"));

	FighterGameMode->CheckGameOverConditions();
}

// network session

void UUMUGameInstance::HostGame(const FString& MapName)
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true, TEXT("?listen"));
}

void UUMUGameInstance::JoinGame(const FString& MapName, const FString& HostCode)
{
    FString IP = HostCodeToIP(HostCode);

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FString URL = FString::Printf(TEXT("%s"), *IP);
        PC->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
    }
}

FString UUMUGameInstance::LocalIPToHostCode(const FString& IP) const
{
    FString CleanIP = IP.Replace(TEXT("."), TEXT(""));
    int32 IPNum = FCString::Atoi(*CleanIP);
    int32 Encoded = IPNum * 37 + 1234;
    return FString::Printf(TEXT("%X"), Encoded);
}


FString UUMUGameInstance::GetMyHostCode()
{
    FString IP = GetLocalIPAddress();
    return LocalIPToHostCode(IP);
}

FString UUMUGameInstance::GetLocalIPAddress() const
{
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (SocketSubsystem)
    {
        bool bCanBind = false;
        TSharedPtr<FInternetAddr> Addr = SocketSubsystem->GetLocalHostAddr(*GLog, bCanBind);
        return Addr->ToString(false);
    }
    return TEXT("0.0.0.0");
}

FString UUMUGameInstance::HostCodeToIP(const FString& Code) const
{
    int32 EncodedNum = FParse::HexNumber(*Code);
    int32 Decoded = (EncodedNum - 1234) / 37;

    FString Raw = PadLeft(FString::FromInt(Decoded), 12, '0');
    FString IP = FString::Printf(TEXT("%s.%s.%s.%s"),
        *Raw.Mid(0, 3),
        *Raw.Mid(3, 3),
        *Raw.Mid(6, 3),
        *Raw.Mid(9, 3));

    return IP;
}

FString UUMUGameInstance::PadLeft(const FString& Input, int32 TotalLength, TCHAR PadChar) const
{
    int32 PadCount = FMath::Max(0, TotalLength - Input.Len());
    return FString::ChrN(PadCount, PadChar) + Input;
}
