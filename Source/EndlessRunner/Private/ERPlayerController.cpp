// Fill out your copyright notice in the Description page of Project Settings.

#include "ERPlayerController.h"
#include "ERPawn.h"

void AERPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	if (aPawn)
		MyPawn = Cast<AERPawn>(aPawn);
	if (MyPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast Success and Mypawn is %s"), *MyPawn->GetName());
		MyPawn->OnPawnDeath.AddUniqueDynamic(this, &AERPlayerController::OnPawnDeath);
	}
		
}

void AERPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!MyPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller is not possessing Pawn. Check"));
		return;
	}
	FVector FForce;
	if (!bBrake)
	{
		if(MyPawn->GetVelocity().X < MaxVelocity)
			FForce = MyPawn->StaticMesh->GetMass() * FVector(Acceleration, 0, 0);
	}
	else if (bBrake)
	{
		if(MyPawn->GetVelocity().X > MinVelocity)
			FForce = MyPawn->StaticMesh->GetMass() * FVector(Deceleration, 0, 0);
	}

	MyPawn->StaticMesh->AddForce(FForce);

}

void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->InputComponent->BindAction("Brake", IE_Pressed, this, &AERPlayerController::ToggleBrake);
	this->InputComponent->BindAction("Brake", IE_Released, this, &AERPlayerController::ToggleBrake);
	this->InputComponent->BindAxis("MoveRight", this, &AERPlayerController::MoveRight);
}

void AERPlayerController::ToggleBrake()
{
	if (!bBrake) bBrake = true;
	else bBrake = false;
}

void AERPlayerController::MoveRight(float value)
{
	if (!MyPawn) return;
	FVector FForce = value * MyPawn->StaticMesh->GetMass() * FVector(0, SideAcceleration, 0);
	MyPawn->StaticMesh->AddForce(FForce);
}

void AERPlayerController::OnPawnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("On Pawn Death in Player Controller"));
	MyPawn->SetLifeSpan(0.01f);
	this->StartSpectatingOnly();
}