// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshair)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshair)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshair)
		float LineTraceRange = 1000000;



private:
	//Start the tank moving the barrel so that a shot would hit where
	//the crosshair intersects the world
	void AimTowardCrosshair();

	//Returns an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreeLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;


};
