// Fill out your copyright notice in the Description page of Project Settings.

#include "ERFloor.h"
#include "ERHitInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AERFloor::AERFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	this->SetRootComponent(StaticMesh);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	BoxCompLeft = CreateDefaultSubobject<UBoxComponent>(FName("Box Component Left"));
	BoxCompLeft->SetupAttachment(this->RootComponent);
	BoxCompLeft->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCompLeft->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	BoxCompRight = CreateDefaultSubobject<UBoxComponent>(FName("Box Component Right"));
	BoxCompRight->SetupAttachment(this->RootComponent);
	BoxCompRight->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCompRight->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	BoxCompEndOverlap = CreateDefaultSubobject<UBoxComponent>(FName("Box Component End Overlap"));
	BoxCompEndOverlap->SetupAttachment(this->RootComponent);
	BoxCompEndOverlap->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AERFloor::BeginPlay()
{
	Super::BeginPlay();
	BoxCompEndOverlap->OnComponentEndOverlap.AddDynamic(this, &AERFloor::OnEndOverlap);
}

void AERFloor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		IERHitInterface * PawnHit = Cast<IERHitInterface>(OtherActor);
		if (PawnHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Passed by Floor %s"), *this->GetName());
			PlayerPassed.Broadcast();
			
		}
	}
}

