// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}


//Start the tank moving the barrel so that a shot would hit where
//the crosshair intersects the world
void ATankPlayerController::AimTowardCrosshair()
{
	if(!GetPawn()) {return;} //In the case nothing is possesed.
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;//Out parameter
	bool IsAHitLocation = GetSightRayHitLocation(HitLocation);

	if (IsAHitLocation) //Has "side-effect", is going to ray trace 
	{
		AimingComponent->AimAtTarget(HitLocation, AimingComponent->ProjectileLaunchSpeed);
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	
	//Find the crosshair position in pixel coorinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);	
	}


	//TODO The turret doesn't move when crosshair is on the sky. needs to fix this.
	return false;
}

//"De-project" 2D crosshair screen location to a Out 3D world direction unit vector 
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; //not used, just needed to call the DeprojectScreenPositionToWorld function

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OUTPARAM OutLookDirection);

}

//does a line trace and Out params the Impact Point (the world location of the hit) or a vector of all zeros if no hit.
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FCollisionParameters Params;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());
	
	//could also use GetHitResultAtScreenPosition if input param is changed to 2d
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + LookDirection * LineTraceRange, ECollisionChannel::ECC_Camera, CollisionParams))
	{
			OutHitLocation = HitResult.ImpactPoint;
			return true;	
	}
	OutHitLocation = FVector(0);
	return false;
}
