#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestMultiplayinstace.generated.h"

UCLASS()
class UMUSMASH_API UTestMultiplayinstace : public UGameInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Network")
    void HostGame(const FString& MapName);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void JoinGame(const FString& MapName, const FString& HostCode);

    UFUNCTION(BlueprintCallable, Category = "Network")
    FString GetMyHostCode();


    FString PadLeft(const FString& Input, int32 TotalLength, TCHAR PadChar = '0') const;

    FString LocalIPToHostCode(const FString& IP) const;
    FString HostCodeToIP(const FString& Code) const;

    FString GetLocalIPAddress() const;
};
