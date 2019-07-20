// CopyRight Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUTPARAM

//Forward Declarations
class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crosshair")
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crosshair")
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crosshair")
		float LineTraceRange = 1000000;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	//Fires an Event in derived blueprint that controls if the player UI is added to the viewport
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	//Start the tank moving the barrel so that a shot would hit where
	//the crosshair intersects the world
	void AimTowardCrosshair();

	//Returns an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreeLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;


};
