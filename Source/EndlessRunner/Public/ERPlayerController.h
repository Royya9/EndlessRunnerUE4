// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ERPlayerController.generated.h"

class AERPawn;
/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AERPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void Possess(APawn* aPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	float Acceleration = 5000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	float Deceleration = -10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	float MaxVelocity = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	float MinVelocity = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	float SideAcceleration = 250.f;

	void ToggleBrake();

	void MoveRight(float value);

	UFUNCTION()
	void OnPawnDeath();

private:

	AERPawn * MyPawn = nullptr;
	bool bBrake = false;
};
