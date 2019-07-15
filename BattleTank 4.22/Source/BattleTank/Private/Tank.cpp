// Copyright Robert Hinds

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankMovementComponent.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::SetMyMoveComp(UTankMovementComponent * MyTankMovementComponent)
{
	if (!ensure(MyTankMovementComponent)) { return;  }
	this->TankMovementComponent = MyTankMovementComponent;
}

void ATank::SetMyAimComp(UTankAimingComponent * MyTankAimingComponent)
{
	if (!ensure(MyTankAimingComponent)) { return; }
	this->TankAimingComponent = MyTankAimingComponent;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP begin Play to run!
	verifyf(ProjectileBlueprint, TEXT("Projectile Blueprint Not Set!"))
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAxis("Move Forward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &ATank::MoveRight);
	PlayerInputComponent->BindAxis("Left Track Throttle", this, &ATank::SetLeftThrottle);
	PlayerInputComponent->BindAxis("Right Track Throttle", this, &ATank::SetRightThrottle);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAtTarget(HitLocation, LaunchSpeed);	
}

///NOTE: the fact the projectile's location and rotation are set to the socket's
/// is used by the LaunchProjectile function of the Projectile class. 
/// it is assumed that the projectile is facing the correct direction when LaunchProjectile function is called.
//Fires a projectile if it has been X number of seconds from the last time a projectile was actually launched.
void ATank::Fire()
{
	UTankBarrel* Barrel = TankAimingComponent->GetBarrelReference();
	if (!ensure(Barrel)) { return; }

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReloaded)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void ATank::MoveForward(float amt)
{	
	if (!ensure(TankMovementComponent)) { return; }

	TankMovementComponent->IntendMoveForward(amt);
}

void ATank::MoveRight(float amt)
{
	if (!ensure(TankMovementComponent)) { return; }

	TankMovementComponent->IntendMoveRight(amt);
}


void ATank::SetLeftThrottle(float amt)
{
	if (!ensure(TankMovementComponent)) { return; }

	TankMovementComponent->SetLeftTrackThrottle(amt);
}

void ATank::SetRightThrottle(float amt)
{
	if (!ensure(TankMovementComponent)) { return; }

	TankMovementComponent->SetRightTrackThrottle(amt);
}
