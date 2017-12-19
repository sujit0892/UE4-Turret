// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/BluePrint/UserWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TURRET_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Load();
	void setText(int Score, int Health);
	void OnGameOver(int Score);

	UPROPERTY()
		UTextBlock* ScoreText;
	
	
	
	
};
