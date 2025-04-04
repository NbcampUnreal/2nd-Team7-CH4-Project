

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMUPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class UMUSMASH_API AUMUPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUMUPlayerController();
	void BeginPlay() override;
	UPROPERTY()
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY()
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY()
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY()
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY()
	TObjectPtr<UInputAction> SmashAction;
	UPROPERTY()
	TObjectPtr<UInputAction> ShieldAction;
private:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> MappingContext;
};
