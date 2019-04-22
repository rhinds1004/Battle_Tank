// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))
	ATank* debugTank = GetControlledTank();
	if (debugTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling: %s"), *(debugTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank pawn found!"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Start the tank moving the barrel so that a shot would hit where
//the crosshair intersects the world
void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }
	//Get world location if linetrace through
		//If it hits landscape
			//Tell controlled tank to aim this point
}




