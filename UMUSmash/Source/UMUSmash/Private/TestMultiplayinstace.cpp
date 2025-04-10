#include "TestMultiplayinstace.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

void UTestMultiplayinstace::HostGame(const FString& MapName)
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true, TEXT("?listen"));
}

void UTestMultiplayinstace::JoinGame(const FString& MapName, const FString& HostCode)
{
    FString IP = HostCodeToIP(HostCode);

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FString URL = FString::Printf(TEXT("%s"), *IP);
        PC->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
    }
}

FString UTestMultiplayinstace::LocalIPToHostCode(const FString& IP) const
{
    FString CleanIP = IP.Replace(TEXT("."), TEXT(""));
    int32 IPNum = FCString::Atoi(*CleanIP);
    int32 Encoded = IPNum * 37 + 1234;
    return FString::Printf(TEXT("%X"), Encoded);
}


FString UTestMultiplayinstace::GetMyHostCode()
{
    FString IP = GetLocalIPAddress();
    return LocalIPToHostCode(IP);
}

FString UTestMultiplayinstace::GetLocalIPAddress() const
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

FString UTestMultiplayinstace::HostCodeToIP(const FString& Code) const
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

FString UTestMultiplayinstace::PadLeft(const FString& Input, int32 TotalLength, TCHAR PadChar) const
{
    int32 PadCount = FMath::Max(0, TotalLength - Input.Len());
    return FString::ChrN(PadCount, PadChar) + Input;
}


