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

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, GetBarrelReference()->GetSocketLocation(FName("Projectile")), GetBarrelReference()->GetSocketRotation(FName("Projectile")));
}