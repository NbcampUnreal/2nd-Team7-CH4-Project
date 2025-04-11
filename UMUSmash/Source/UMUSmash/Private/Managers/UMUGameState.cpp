


#include "Managers/UMUGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/UMUFightGameMode.h"
#include "Managers/UMUGameInstance.h"
#include "Net/UnrealNetwork.h"

AUMUGameState::AUMUGameState()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void AUMUGameState::MulticastRPCIsGameOver_Implementation()
{
	SlowMotionEffect();
}

void AUMUGameState::SlowMotionEffect() 
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
	
	TWeakObjectPtr<AUMUGameState> WeakThisPtr(this);
	FTimerHandle FinalGameStatsHandle;
	GetWorld()->GetTimerManager().SetTimer(
		FinalGameStatsHandle,FTimerDelegate::CreateLambda([WeakThisPtr]
		{
			if (WeakThisPtr.IsValid() && WeakThisPtr->GetWorld())
			{
				UGameplayStatics::SetGlobalTimeDilation(WeakThisPtr->GetWorld(), 1.0f);
			}
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

void AUMUGameState::StartCountdown()
{
	bUseTimer = true;
	if (HasAuthority())
	{
		CountdownEndTime = GameInstance->GetMin() * 60.0f;
		TWeakObjectPtr<AUMUGameState> WeakThisPtr(this);
		GetWorld()->GetTimerManager().SetTimer(
			CountdownTimerHandle, FTimerDelegate::CreateLambda([WeakThisPtr]()
			{
				if (WeakThisPtr.IsValid() && WeakThisPtr->GetWorld())
				{
					WeakThisPtr->UpdateCountdown();	
				}
			}),
			1.0f,
			true,
			-1);
	}
}

void AUMUGameState::UpdateCountdown()
{
	if (HasAuthority())
	{
		const float CurrentTime = GetWorld()->GetTimeSeconds();
		Seconds = FMath::Max(0.0f, CountdownEndTime - CurrentTime);
		GameInstance->SetSeconds(Seconds);

		if (Seconds <= 0.0f)
		{
			GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
			bUseTimer = false;
		}
	}
}

void AUMUGameState::OnRep_UpdateSeconds()
{
	LastReplicatedSeconds = Seconds;
	if (GetWorld())
	{
		LastReplicatedTimestamp = GetWorld()->GetTimeSeconds();
	}
}

void AUMUGameState::UpdateInterpolatedTime()
{
	if (!HasAuthority())
	{
		const float CurrentTime = GetWorld()->GetTimeSeconds();
		InterpolatedTime = LastReplicatedSeconds - (CurrentTime - LastReplicatedTimestamp);
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
	DOREPLIFETIME(AUMUGameState, Seconds);
	DOREPLIFETIME(AUMUGameState, bUseTimer);
}

void AUMUGameState::BeginPlay()
{
	Super::BeginPlay();

	InitState();
}

void AUMUGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInterpolatedTime();
}
