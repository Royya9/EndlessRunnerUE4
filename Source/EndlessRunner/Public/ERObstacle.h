// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERObstacle.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerPassed);

UCLASS()
class ENDLESSRUNNER_API AERObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AERObstacle();

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent * StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent * BoxCompCollision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent * BoxCompOverlap = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FPlayerPassed PlayerPassed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	   	
};
