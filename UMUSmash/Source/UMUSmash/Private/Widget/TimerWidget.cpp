#include "Widget/TimerWidget.h"
#include "Components/TextBlock.h"
#include "Managers/UMUGameState.h"


void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(CountdownText);
}

void UTimerWidget::UpdateCountdownWidget()
{
	auto* World = GetWorld();
	if (World)
	{
		auto* GameState = World->GetGameState<AUMUGameState>();
		if (GameState)
		{
			const double RemainingSeconds = GameState->GetInterpolatedTime();
			int32 Minutes = FMath::FloorToInt(RemainingSeconds / 60.0f);
			int32 Seconds = FMath::FloorToInt(RemainingSeconds) % 60;

			FText NewCount = FText::FromString(FString::Printf(TEXT("Time\n%02d:%02d"), Minutes, Seconds));
			CountdownText->SetText(NewCount);

			FSlateColor NewColor;
			if (RemainingSeconds <= 10)
			{
				NewColor = FSlateColor(FLinearColor::Red);

				if (!GetWorld()->GetTimerManager().IsTimerActive(BlinkTimerHandle))
				{
					GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &UTimerWidget::ToggleBlink, 0.5f, true);
				}
			}
			else if (RemainingSeconds <= 30)
			{
				NewColor = FSlateColor(FLinearColor(1.0f, 0.5f, 0.0f));

				GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
				CountdownText->SetRenderOpacity(1.0f);
			}
			else
			{
				NewColor = FSlateColor(FLinearColor::White);

				GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
				CountdownText->SetRenderOpacity(1.0f);
			}

			CountdownText->SetColorAndOpacity(NewColor);
		}
	}
}


void UTimerWidget::ToggleBlink()
{
	if (CountdownText)
	{
		bIsBlinkVisible = !bIsBlinkVisible;
		CountdownText->SetRenderOpacity(bIsBlinkVisible ? 1.0f : 0.2f);
	}
}
