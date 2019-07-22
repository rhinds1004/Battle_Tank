// Copyright Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankTrack;
class UTankMovementComponent;



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void MoveForward(float amt);

	UFUNCTION()
	void MoveRight(float amt);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetLeftThrottle(float amt);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetRightThrottle(float amt);



protected:


	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 7000; 
	

	


	

};
