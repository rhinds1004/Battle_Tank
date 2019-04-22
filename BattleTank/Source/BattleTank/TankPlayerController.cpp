// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


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
	FVector HitLocation;//Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to ray trace 
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())

					//TODO Tell controlled tank to aim this point
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	
	// get coords of crosshair dot.
	//Send a raytrace through the crosshair dot 
	//Check if raytrace hits an object. if yes, check if terrain
	//set OutHitLocation to the world vector hit by the raytrace
	//return result of raytrace check
	OutHitLocation = FVector(1.0);
	return true;
}



