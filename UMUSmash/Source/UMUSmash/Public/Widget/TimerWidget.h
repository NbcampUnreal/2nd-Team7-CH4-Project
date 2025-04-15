#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;

UCLASS()
class UMUSMASH_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCountdownWidget();

protected:
	virtual void NativeConstruct() override;

	/** �����̴� ȿ���� ���� �Լ� */
	void ToggleBlink();

protected:
	/** �������� ���ε��� ī��Ʈ�ٿ� �ؽ�Ʈ */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountdownText;

	/** ������ ȿ���� ���� Ÿ�̸� �ڵ� */
	FTimerHandle BlinkTimerHandle;

	/** �ؽ�Ʈ�� ���� ���̴��� ���� */
	bool bIsBlinkVisible = true;
};
