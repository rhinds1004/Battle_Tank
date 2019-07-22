// Copyright Robert Hinds

#include "Tank.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TankMovementComponent.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP begin Play to run!
	TankMovementComponent = FindComponentByClass<UTankMovementComponent>();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &ATank::MoveRight);
	PlayerInputComponent->BindAxis("Left Track Throttle", this, &ATank::SetLeftThrottle);
	PlayerInputComponent->BindAxis("Right Track Throttle", this, &ATank::SetRightThrottle);

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
