// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"))
		ATank* debugTank = GetControlledTank();
	if (debugTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlling: %s"), *(debugTank->GetName()))
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

