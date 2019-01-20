// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ERHitInterface.h"
#include "ERPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnState);

UCLASS()
class ENDLESSRUNNER_API AERPawn : public APawn, public IERHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AERPawn();

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent * StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UCameraComponent * FollowCamera = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USpringArmComponent * SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent * BoxComp = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger Reaction")
		bool ReactToTrigger();
		virtual bool ReactToTrigger_Implementation() override;

	FPawnState OnPawnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
