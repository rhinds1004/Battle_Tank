// Robert Hinds

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 
	
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
		Barrel = BarrelToSet;
		Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//Prevents tanks from firing right at spawn 
	LastFireTime = GetWorld()->GetTimeSeconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (AmmoCount <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
		LastFireTime = GetWorld()->GetTimeSeconds(); //Ensure if ammo is replenished, tank can't instantly fire again.
	}
	else if (GetRemaingReloadTime() > 0.f)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

//Currently set to do no trace. Maybe tracefull path better option. use the params to get what was hit and use that for damage?
void UTankAimingComponent::AimAtTarget(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }
	
	TArray<AActor*>ActorsToIgnore;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // getsocketlocation will return the component location if socket isn't found
//TODO do we not want to know what the projectile hit? If so using do not trace wont work. Set
	bool SuggestProjectileVelocityResult = UGameplayStatics::SuggestProjectileVelocity(this, OUTPARAM OutLaunchVelocity, StartLocation, HitLocation,
		LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, ActorsToIgnore, false);
	if (SuggestProjectileVelocityResult)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowrds(AimDirection);
			
	}
	else
	{
	// TODO what to do if no solution found?
	
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector DirectionToAim)
{
	if (!ensure(Barrel)) { return; }

	FRotator BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = DirectionToAim.ToOrientationRotator();
	FRotator DeltaRotator = (AimAsRotator - BarrelRotation);
	Barrel->ElevateBarrel(DeltaRotator.GetNormalized().Pitch); // GetNormalized: "Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation."

}


void UTankAimingComponent::MoveTurretTowrds(FVector DirectionToAim)
{
	if (!ensure(Turret)) { return; }

	FRotator TurretRotation = Turret->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = DirectionToAim.ToOrientationRotator();
	FRotator DeltaRotator = AimAsRotator - TurretRotation;
	Turret->RotateTurret(DeltaRotator.GetNormalized().Yaw); // GetNormalized: "Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation."
}



///NOTE: the fact the projectile's location and rotation are set to the socket's
/// is used by the LaunchProjectile function of the Projectile class. 
/// it is assumed that the projectile is facing the correct direction when LaunchProjectile function is called.
//Fires a projectile if it has been X number of seconds from the last time a projectile was actually launched.
void UTankAimingComponent::Fire()
{

	if (!ensure(this->Barrel)) { return; }

	if (!ensure(ProjectileBlueprint)) { return; }



	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		SetAmmoCount(AmmoCount - 1);
	}
}

//Returns false when barrel is pointing "directly" at the UI recticule 
bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }	

	FVector BarrelForwardVector = Barrel->GetForwardVector().GetSafeNormal();
	return !BarrelForwardVector.Equals(AimDirection, .01f);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

void UTankAimingComponent::SetAmmoCount(int NewAmmoCount)
{
	if (AmmoCount > 0)
	{
		AmmoCount = NewAmmoCount;
	}
	else
	{
		AmmoCount = 0;
	}
	
}

//Returns how much longer until the tank is ready to fire. If ready to fire now, 0.f is returned.
//Uses world time, member variables ReloadTimeInSeconds and LastFireTime
//Returns max reload time if ammo is zero.
float UTankAimingComponent::GetRemaingReloadTime() const
{
	
	float TimeRemaining =  ReloadTimeInSeconds - (GetWorld()->GetTimeSeconds() - LastFireTime);
	if (TimeRemaining <= 0.f)
	{
		TimeRemaining = 0.f;
	}
	else if (AmmoCount == 0)
	{
		TimeRemaining = ReloadTimeInSeconds;
	}
	return TimeRemaining;
}

