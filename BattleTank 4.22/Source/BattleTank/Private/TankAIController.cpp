// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "Engine/World.h"

#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Tank.h"
#include "TankAimingComponent.h"

//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		//Move to player
		MoveToActor(PlayerTank, AcceptanceRadius); //check radius is in CM comes from Unreal Engines's AI pathfinding which is accessible due to inheriting from AI Controller
		//Aim towards player	
		AimingComponent->AimAtTarget(PlayerTank->GetActorLocation(), AimingComponent->ProjectileLaunchSpeed);
		//TODO only fire when barrel is pointed at player
		ControlledTank->Fire();
	}
}
