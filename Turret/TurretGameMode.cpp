// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretGameMode.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameWidget.h"

void ATurretGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(Startingwidget);
	((UGameWidget*)CurrentWidget)->Load();
	((UGameWidget*)CurrentWidget)->setText(score, health);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &ATurretGameMode::Restart).bExecuteWhenPaused=true;
}

void ATurretGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer <= 0.0f)
	{
		float difficultyPercentage = FMath::Min(GameTimer / TIME_MINIMUM_TO_MAXIMUM, 1.0f);
		EnemyTimer = MAXIMUM_INTERVAL - (MAXIMUM_INTERVAL - MINIMUM_INTERVAL)*difficultyPercentage;
		UWorld* World=GetWorld();
		if (World)
		{
			float distance = 900.0f;
			float RandomAngle = FMath::RandRange(0.0f, 360.0f);
			FVector Location = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
			FVector EnemyLocation = Location;
			EnemyLocation.X = FMath::Cos(RandomAngle*3.14f / 180.0f)*distance;
			EnemyLocation.Y = FMath::Sin(RandomAngle*3.14f / 180.0f)*distance;
			EnemyLocation.Z = 210.0f;
			AEnemyController* enemy = World->SpawnActor<AEnemyController>(EnemyBlueprint, EnemyLocation, FRotator::ZeroRotator);
			enemy->Direction = (Location - EnemyLocation).GetSafeNormal();
		}
	}
}

void ATurretGameMode::ChangeScore(int value)
{
	score += value;
	((UGameWidget*)CurrentWidget)->setText(score, health);
}
void ATurretGameMode::ChangeHealth(int value)
{
	health += value;
	((UGameWidget*)CurrentWidget)->setText(score, health);
	if (health <= 0)
	{
		this->OnGameOver();
	}
}

void ATurretGameMode::OnGameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	((UGameWidget*)CurrentWidget)->OnGameOver(score);
}

void ATurretGameMode::Restart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

void ATurretGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidget)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidget);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}