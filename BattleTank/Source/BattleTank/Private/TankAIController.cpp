// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
		//TODO move to player
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), AcceptanceRadius); //check radius is in CM
		//Aim towards player	
		ControlledTank->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
		//TODO only fire when barrel is pointed at player
		ControlledTank->Fire();	
}
