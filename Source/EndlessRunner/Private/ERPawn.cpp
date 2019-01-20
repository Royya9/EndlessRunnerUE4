// Fill out your copyright notice in the Description page of Project Settings.

#include "ERPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AERPawn::AERPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	this->SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetGenerateOverlapEvents(false);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("Box Component"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetGenerateOverlapEvents(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	FollowCamera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void AERPawn::BeginPlay()
{
	Super::BeginPlay();

}

bool AERPawn::ReactToTrigger_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Hit detected in Player"));
	OnPawnDeath.Broadcast();
//	this->SetLifeSpan(0.01f);
	return true;
}

