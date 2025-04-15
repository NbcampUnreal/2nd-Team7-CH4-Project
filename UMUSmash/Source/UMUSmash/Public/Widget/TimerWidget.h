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

	/** 깜빡이는 효과를 위한 함수 */
	void ToggleBlink();

protected:
	/** 위젯에서 바인딩된 카운트다운 텍스트 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountdownText;

	/** 깜빡임 효과를 위한 타이머 핸들 */
	FTimerHandle BlinkTimerHandle;

	/** 텍스트가 현재 보이는지 여부 */
	bool bIsBlinkVisible = true;
};
