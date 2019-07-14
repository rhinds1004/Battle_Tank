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
	UTankBarrel* GetBarrelReference();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAtTarget(FVector HitLocation, float LaunchSpeed);



private:
	UPROPERTY()
		UTankBarrel* Barrel = nullptr;
	UPROPERTY()
		UTankTurret* Turret = nullptr;



	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowrds(FVector AimDirection);
	

	

};
