// Robert Hinds

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Tank.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret * TurretToSet)
{
	if (ensure(BarrelToSet) && ensure(TurretToSet))
	{
		Barrel = BarrelToSet;
		Turret = TurretToSet;
	}

	//TODO REmove this workaround. Needed because the reference to the tank movement component is getting nulled in the tank class after this function returns. Need to find out why.
	ATank* OwnerTank = Cast<ATank>(GetOwner());
	OwnerTank->SetMyAimComp(this);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (ensure(BarrelToSet))
	{
		Barrel = BarrelToSet;
	}
	
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (ensure(TurretToSet))
	{
		Turret = TurretToSet;
	}
}

UTankBarrel* UTankAimingComponent::GetBarrelReference()
{
	return Barrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Currently set to do no trace. Maybe tracefull path better option. use the params to get what was hit and use that for damage?
void UTankAimingComponent::AimAtTarget(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	
	TArray<AActor *>ActorsToIgnore;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // getsocketlocation will return the component location if socket isn't found
//TODO do we not want to know what the projectile hit? If so using do not trace wont work. Set
	bool SuggestProjectileVelocityResult = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, HitLocation,
		LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, ActorsToIgnore, false);
	if (SuggestProjectileVelocityResult)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowrds(AimDirection);
			
	}
	else
	{
	// TODO what to do if no solution found?
	
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = AimDirection.ToOrientationRotator();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->ElevateBarrel(DeltaRotator.Pitch); 
}

void UTankAimingComponent::MoveTurretTowrds(FVector AimDirection)
{
	FRotator TurretRotation = Turret->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = AimDirection.ToOrientationRotator();
	FRotator DeltaRotator = AimAsRotator - TurretRotation;
	Turret->RotateTurret(DeltaRotator.Yaw);
}