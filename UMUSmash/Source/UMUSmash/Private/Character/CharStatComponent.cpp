


#include "Character/CharStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/BaseCharacter.h"
#include <Managers\UMUGameInstance.h>

// Sets default values for this component's properties
UCharStatComponent::UCharStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharStatComponent::BeginPlay()
{
	Super::BeginPlay();

	Parent = Cast<ABaseCharacter>(GetOwner());

	if (!Parent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMU_Character_Stats: Parent casting fail"));
	}

	// 밑의 부분은 스톡을 추가하는 구문
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UUMUGameInstance* FighterGameInstance = Cast<UUMUGameInstance>(GameInstance);

	if (!FighterGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMUGameInstance casting fail"));
	}

	EInGameModes CurrentSubGameMode = FighterGameInstance->GetSubGameMode();

	if (CurrentSubGameMode == EInGameModes::Stock)
	{
		Stock = FighterGameInstance->GetStockCount();
	}
}

void UCharStatComponent::ScreenShake(float RumbleInten, float RumbleDuration)
{
	check(Parent && ShakeClass);
	FVector Epicenter = Parent->GetActorLocation();
	UGameplayStatics::PlayWorldCameraShake(
		GetWorld(),
		ShakeClass,
		Epicenter,
		100.0f,     // Inner Radius
		10000.0f,   // Outer Radius
		1.0f        // Falloff
	);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), Parent->PlayerNo);
	if (!PC) return;

	// 3. 진동 효과
	PC->PlayDynamicForceFeedback(
		RumbleInten,
		RumbleDuration,
		true, true, true, true
	);
}

void UCharStatComponent::TakeDamage(float Dam)
{
	check(Parent);
	if (Parent->HitStates == EHitStateType::Normal)
	{
		Percent += Dam;

		SuperGage += (int32)Dam % 2;
	}
}

