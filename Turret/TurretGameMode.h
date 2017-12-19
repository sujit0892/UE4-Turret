// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TurretGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TURRET_API ATurretGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	float MINIMUM_INTERVAL = 0.5f;
	float MAXIMUM_INTERVAL = 2.0f;
	float TIME_MINIMUM_TO_MAXIMUM = 30.0f;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void ChangeHealth(int value);
	void ChangeScore(int value);
	void OnGameOver();
	void Restart();

	float GameTimer;
	float EnemyTimer;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyController> EnemyBlueprint;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidget);

protected:
	int health=100;
	int score=0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> Startingwidget;

	UUserWidget* CurrentWidget;
	
	
	
};
