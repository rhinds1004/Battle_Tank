// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

#define OUTPARAM
//Enum
UENUM()
enum class EFiringState : uint8
{
	OutOfAmmo,
	Reloading,
	Aiming,
	Locked
	
};


//Forward Declarations
class UTankBarrel;
class UTankTurret;

//Owns the barrel and turrent of the tank. And controls moving components to the proper locations.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<class AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "State")
		int AmmoCount = 2;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAtTarget(FVector HitLocation, float LaunchSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ProjectileLaunchSpeed = 7000;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION()
	bool IsBarrelMoving();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "State")
		int32 GetAmmoCount() const;

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetAmmoCount(int NewAmmoCount);

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetRemaingReloadTime() const;



private:
	UPROPERTY()
		UTankBarrel* Barrel = nullptr;
	UPROPERTY()
		UTankTurret* Turret = nullptr;

	double LastFireTime = 0;



	FVector AimDirection = FVector(0);

	void MoveBarrelTowards(FVector DirectionToAim);

	void MoveTurretTowrds(FVector DirectionToAim);


	

	

};
