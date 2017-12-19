// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurretGameMode.h"
#include "GameFramework/Character.h"


// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::onOverlap);
		RootComponent = RootBox;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Direction.X*Speed*DeltaTime;
	NewLocation.Y += Direction.Y*Speed*DeltaTime;
	SetActorLocation(NewLocation);


}

void  AEnemyController::onOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromsweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains("Projectile"))
	{
		((ATurretGameMode*)GetWorld()->GetAuthGameMode())->ChangeScore(50);
		OtherActor->Destroy();
		this->Destroy();
		
	}
	else if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		this->Destroy();
		((ATurretGameMode*)GetWorld()->GetAuthGameMode())->ChangeHealth(-20);
	}

}

