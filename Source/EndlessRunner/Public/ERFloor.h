// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERFloor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerPassedFloor);

UCLASS()
class ENDLESSRUNNER_API AERFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AERFloor();

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent * StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent * BoxCompLeft = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent * BoxCompRight = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Setup")
	UBoxComponent * BoxCompEndOverlap = nullptr;

	FPlayerPassedFloor PlayerPassed;

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
};
