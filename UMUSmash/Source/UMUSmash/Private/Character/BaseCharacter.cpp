#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character\UMUPlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

