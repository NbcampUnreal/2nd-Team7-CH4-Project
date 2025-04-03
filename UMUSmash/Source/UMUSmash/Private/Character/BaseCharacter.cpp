#include "Character/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character\UMUPlayerController.h"
#include <Net\UnrealNetwork.h>

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

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, PlayerAcceleration);
	DOREPLIFETIME(ABaseCharacter, JumpCount);
	DOREPLIFETIME(ABaseCharacter, bCanMove);
	DOREPLIFETIME(ABaseCharacter, FaceDirection);
	DOREPLIFETIME(ABaseCharacter, bCanFlip);
	DOREPLIFETIME(ABaseCharacter, LeftRight);
	DOREPLIFETIME(ABaseCharacter, UpDown);
	DOREPLIFETIME(ABaseCharacter, Direction);
	DOREPLIFETIME(ABaseCharacter, ZPos);
	DOREPLIFETIME(ABaseCharacter, YPos);
	DOREPLIFETIME(ABaseCharacter, FootZPos);
	DOREPLIFETIME(ABaseCharacter, Location);
	DOREPLIFETIME(ABaseCharacter, LocationFeet);
	DOREPLIFETIME(ABaseCharacter, CharState);
	DOREPLIFETIME(ABaseCharacter, AttackType);
	DOREPLIFETIME(ABaseCharacter, AbilityType);
	DOREPLIFETIME(ABaseCharacter, DirectionType);
	
}

