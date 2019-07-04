// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, Category = Firing)
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UFUNCTION()
	void MoveForward(float amt);

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetLeftThrottle(float amt);

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetRightThrottle(float amt);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetLeftTrack(UTankTrack* TrackToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRightTrack(UTankTrack* TrackToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		UTankBarrel* GetBarrelReference();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
		UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 7000; 
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;
	
	UPROPERTY()
	UTankTrack* LeftTrack = nullptr;

	UPROPERTY()
		UTankTrack* RightTrack = nullptr;

};
