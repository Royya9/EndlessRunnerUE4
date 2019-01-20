// Fill out your copyright notice in the Description page of Project Settings.

#include "ERGameModeBase.h"
#include "ERPlayerController.h"
#include "ERPawn.h"
#include "ERGameStateBase.h"
#include "ERObstacle.h"
#include "ERFloor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"


AERGameModeBase::AERGameModeBase()
{
	this->PlayerControllerClass = AERPlayerController::StaticClass();
	this->DefaultPawnClass = AERPawn::StaticClass();
	this->GameStateClass = AERGameStateBase::StaticClass();
	
}

void AERGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<AERPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	FTimerHandle TimerHandleObstacle, TimerHandleFloor;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleObstacle, this, &AERGameModeBase::GenerateObstacles, 3.f, true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandleFloor, this, &AERGameModeBase::GenerateFloor, 2.f, false);

	for (TActorIterator<AERFloor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AERFloor *FloorPtr = Cast<AERFloor>(*ActorItr);
		if (FloorPtr)
			CurrentFloorPtr = FloorPtr;
	}
}

void AERGameModeBase::GenerateObstacles()
{
	if (!ensure(ObstacleBP) || !ensure(PlayerPawn) || !CurrentFloorPtr) return;
	if (PlayerPawn->GetVelocity().X < 300.f) return;
	FVector PlayerCurrentLocation = PlayerPawn->GetActorLocation();
	FVector SpawnLocation;
	SpawnLocation.X = PlayerCurrentLocation.X + FMath::RandRange(2000.f, 2400.f);
	SpawnLocation.Y = FMath::RandRange(CurrentFloorPtr->BoxCompLeft->GetComponentLocation().Y, CurrentFloorPtr->BoxCompRight->GetComponentLocation().Y);
	SpawnLocation.Z = CurrentFloorPtr->GetActorLocation().Z + 84.f;

	FRotator SpawnRotation = FRotator(0, 0, 0);

	Obstacleptr = GetWorld()->SpawnActor<AERObstacle>(ObstacleBP, SpawnLocation, SpawnRotation);
	Obstacleptr->PlayerPassed.AddDynamic(this, &AERGameModeBase::DestroyObstacle);

}

void AERGameModeBase::GenerateFloor()
{
	if (!ensure(FloorBP) || !ensure(PlayerPawn) ) return;
	if (PlayerPawn->GetVelocity().X < 300.f) return;
	if (CurrentFloorPtr->IsActorBeingDestroyed()) return;
	if (NextFloorPtr) return;

	FVector FloorCurrentLocation = CurrentFloorPtr->GetActorLocation();
	FVector SpawnLocation;
	SpawnLocation.X = FloorCurrentLocation.X + 2*(CurrentFloorPtr->BoxCompEndOverlap->GetComponentLocation().X - FloorCurrentLocation.X);
	SpawnLocation.Y = FloorCurrentLocation.Y;
	SpawnLocation.Z = FloorCurrentLocation.Z;

	FRotator SpawnRotation = FRotator(0, 0, 0);

	NextFloorPtr = GetWorld()->SpawnActor<AERFloor>(FloorBP, SpawnLocation, SpawnRotation);
	UE_LOG(LogTemp, Warning, TEXT("Floor %s Spawned at %s"), *NextFloorPtr->GetName(), *NextFloorPtr->GetActorLocation().ToString());
	CurrentFloorPtr->PlayerPassed.AddDynamic(this, &AERGameModeBase::DestroyFloor);
}

void AERGameModeBase::DestroyObstacle()
{
	UE_LOG(LogTemp, Warning, TEXT("Obstacle %s is getting destroyed"), *Obstacleptr->GetName());
	Obstacleptr->Destroy();
}

void AERGameModeBase::DestroyFloor()
{
	UE_LOG(LogTemp, Warning, TEXT("Floor %s is getting destroyed"), *CurrentFloorPtr->GetName());
	CurrentFloorPtr->Destroy();
	FTimerHandle FloorHandle;
	GetWorld()->GetTimerManager().SetTimer(FloorHandle, this, &AERGameModeBase::DestroyFloorSub, 0.2f, false);
}

void AERGameModeBase::DestroyFloorSub()
{
	CurrentFloorPtr = NextFloorPtr;
	NextFloorPtr = nullptr;
	this->GenerateFloor();
}