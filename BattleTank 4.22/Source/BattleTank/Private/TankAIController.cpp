// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		//Move to player
		MoveToActor(PlayerTank, AcceptanceRadius); //check radius is in CM
		//Aim towards player	
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//TODO only fire when barrel is pointed at player
		ControlledTank->Fire();
	}
}
