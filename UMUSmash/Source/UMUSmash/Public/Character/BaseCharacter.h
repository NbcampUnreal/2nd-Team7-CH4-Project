

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class UMUSMASH_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& value);
	void Attack();
	void Smash();
	void Shield();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float AttackDamage = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float MoveSpeed = 100.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
