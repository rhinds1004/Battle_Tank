// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Projectile.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//No need to protect points as assed at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}



void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

UTankBarrel* ATank::GetBarrelReference()
{
	return TankAimingComponent->GetBarrelReference();
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATank::Fire);

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
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	auto Barrel = GetBarrelReference();
	
	if (Barrel && IsReloaded)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}