#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character\UMUPlayerController.h"
#include "Abilities\AbilityComponent.h"
#include "Character\LedgeComponent.h"
#include "Character\CharStatComponent.h"
#include <Net\UnrealNetwork.h>
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	LedgeComponent = CreateDefaultSubobject<ULedgeComponent>(TEXT("LedgeComponent"));
	CharStatComponent = CreateDefaultSubobject<UCharStatComponent>(TEXT("CharStatComponent"));
}

void ABaseCharacter::ClearBuffer()
{
	BufferMove = EBufferType::None;
	BufferDirection = EInputDirection::None;
	bBufferdInput = false;
	bBufferdDirection = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, JumpNumber);
	DOREPLIFETIME(ABaseCharacter, Bounce);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AUMUPlayerController* PlayerController = Cast<AUMUPlayerController>(GetController()))
		{


		}
	}
}

