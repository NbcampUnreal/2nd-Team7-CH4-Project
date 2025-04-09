


#include "Managers/UMUGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/UMUFightGameMode.h"
#include "Managers/UMUGameInstance.h"
#include "Net/UnrealNetwork.h"

void AUMUGameState::MulticastRPCIsGameOver_Implementation()
{
	SlowMotionEffect();
}

void AUMUGameState::SlowMotionEffect() const
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);

	FTimerHandle FinalGameStatsHandle;
	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,FTimerDelegate::CreateLambda([this]
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		}),
		0.2f,false, -1);
}

void AUMUGameState::UpdateIsGameOver()
{
	bIsGameOver = GameInstance->IsGameOver();
}

void AUMUGameState::UpdatePlayerLoaded()
{
	if (HasAuthority())
	{
		PlayerLoaded = GameMode->GetPlayerLoaded();
		bIsAllLoaded = GameMode->OnlineAllLoaded();
	}
}

void AUMUGameState::InitState()
{
	auto* CurrentGameInstance = GetGameInstance();
	auto* UMUGameInstance = Cast<UUMUGameInstance>(CurrentGameInstance);
	
	auto* CurrentGameMode = GetWorld()->GetAuthGameMode();
	auto* UMUGameMode = Cast<AUMUFightGameMode>(CurrentGameMode);

	GameInstance = UMUGameInstance;
	GameMode = UMUGameMode;
	
	check(GameInstance)
	check(GameMode)
	
	UpdatePlayerLoaded();
}

void AUMUGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUMUGameState, bIsAllLoaded);
	DOREPLIFETIME(AUMUGameState, PlayerLoaded);
}

void AUMUGameState::BeginPlay()
{
	Super::BeginPlay();

	InitState();
}
