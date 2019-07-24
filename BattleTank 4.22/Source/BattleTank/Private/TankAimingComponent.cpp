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
	PrimaryComponentTick.bCanEverTick = false; 

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
	if (!ensure(Barrel)) { return; }

	FRotator BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = AimDirection.ToOrientationRotator();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->ElevateBarrel(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurretTowrds(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }

	FRotator TurretRotation = Turret->GetForwardVector().ToOrientationRotator();
	FRotator AimAsRotator = AimDirection.ToOrientationRotator();
	FRotator DeltaRotator = AimAsRotator - TurretRotation;
	Turret->RotateTurret(DeltaRotator.Yaw);
}



///NOTE: the fact the projectile's location and rotation are set to the socket's
/// is used by the LaunchProjectile function of the Projectile class. 
/// it is assumed that the projectile is facing the correct direction when LaunchProjectile function is called.
//Fires a projectile if it has been X number of seconds from the last time a projectile was actually launched.
void UTankAimingComponent::Fire()
{

	if (!ensure(this->Barrel)) { return; }

	if (!ensure(ProjectileBlueprint)) { return; }

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReloaded)
	{
		
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}