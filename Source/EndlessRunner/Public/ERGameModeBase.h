// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ERGameModeBase.generated.h"

class AERObstacle;
class AERPawn;
class AERFloor;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AERGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AERGameModeBase();

	virtual void BeginPlay() override;
	void GenerateObstacles();
	void GenerateFloor();
	void DestroyFloorSub();

	UFUNCTION()
	void DestroyObstacle();

	UFUNCTION()
	void DestroyFloor();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AERObstacle> ObstacleBP = NULL;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AERFloor> FloorBP = NULL;

private:

	AERPawn * PlayerPawn = nullptr;
	AERObstacle * Obstacleptr = nullptr;
	AERFloor * CurrentFloorPtr = nullptr;
	AERFloor * NextFloorPtr = nullptr;

};
