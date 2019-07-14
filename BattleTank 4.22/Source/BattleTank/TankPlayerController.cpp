// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component"))
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
		GetControlledTank()->AimAt(HitLocation);
					
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	
	//Find the crosshair position in pixel coorinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);	
	}
	return true;
}

//"De-project" 2D crosshair screen location to a Out 3D world direction unit vector 
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; //not used

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);

}

//does a line trace and Out params the Impact Point (the world location of the hit) or a vector of all zeros if no hit.
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	FCollisionParameters Params;
	
	//could also use GetHitResultAtScreenPosition if input param is changed to 2d
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + LookDirection * LineTraceRange, ECollisionChannel::ECC_Visibility))
	{
		
			OutHitLocation = HitResult.ImpactPoint;
			return true;
		
	}
	OutHitLocation = FVector(0);
	return false;
}
