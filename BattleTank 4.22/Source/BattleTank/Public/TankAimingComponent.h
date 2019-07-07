// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

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

//Holds barrels' poroperties and evelvate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	UTankBarrel* GetBarrelReference();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

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
