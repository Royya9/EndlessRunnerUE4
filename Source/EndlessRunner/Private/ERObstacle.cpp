// Fill out your copyright notice in the Description page of Project Settings.

#include "ERObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ERHitInterface.h"

// Sets default values
AERObstacle::AERObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	this->SetRootComponent(StaticMesh);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	BoxCompCollision = CreateDefaultSubobject<UBoxComponent>(FName("Box Component Collision"));
	BoxCompCollision->SetupAttachment(this->RootComponent);
	BoxCompCollision->SetGenerateOverlapEvents(true);
	
	BoxCompOverlap = CreateDefaultSubobject<UBoxComponent>(FName("Box Component Overlap"));
	BoxCompOverlap->SetupAttachment(this->RootComponent);
	BoxCompOverlap->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AERObstacle::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(BoxCompCollision) || !ensure(BoxCompOverlap)) return;
	BoxCompCollision->OnComponentBeginOverlap.AddDynamic(this, &AERObstacle::OnHit);
	BoxCompOverlap->OnComponentEndOverlap.AddDynamic(this, &AERObstacle::OnEndOverlap);
}

void AERObstacle::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		IERHitInterface * PawnHit = Cast<IERHitInterface>(OtherActor);
		if (PawnHit)
			PawnHit->Execute_ReactToTrigger(OtherActor);
	}
}

void AERObstacle::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		IERHitInterface * PawnHit = Cast<IERHitInterface>(OtherActor);
		if (PawnHit)
		{
			PlayerPassed.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Player Passed by Obstacle %s"), *this->GetName());
		}
	}
}



