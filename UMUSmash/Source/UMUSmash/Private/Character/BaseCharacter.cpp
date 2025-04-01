#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character\UMUPlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Move(const FInputActionValue& value)
{
	FVector2D Direction = value.Get<FVector2D>();
	//AddMovementInput(Direction);
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::Smash()
{
}

void ABaseCharacter::Shield()
{
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
			EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
			EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
			//EnhancedInput->BindAction(PlayerController->CrouchAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Crouch);
			EnhancedInput->BindAction(PlayerController->AttackAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Attack);
			EnhancedInput->BindAction(PlayerController->SmashAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Smash);
			EnhancedInput->BindAction(PlayerController->ShieldAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Shield);
		}
	}
}

