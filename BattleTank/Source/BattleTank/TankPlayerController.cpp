// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))
	ATank* debugTank = GetControlledTank();
	if (debugTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling: %s"), *(debugTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank pawn found!"))
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


