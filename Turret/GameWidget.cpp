// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"


void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("MessageBlock"));
	if (ScoreText == nullptr)
	{
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::setText(int Score, int Health)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(Score) + FString(TEXT("\nHealth : ")) + FString::FromInt(Health)));
	}
}

void UGameWidget::OnGameOver(int Score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Game Over!!!")) + FString(TEXT("\nScore : ")) + FString::FromInt(Score) + FString(TEXT("\nPress R to Restart"))));
	}
}
