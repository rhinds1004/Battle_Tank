// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* debugTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Player controlled tank: %s "), *(playerTank->GetName()))
	}
	else if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank!!!"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank pawn found!"))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		//TODO move to player
		//Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//Fire if ready

	}
}
