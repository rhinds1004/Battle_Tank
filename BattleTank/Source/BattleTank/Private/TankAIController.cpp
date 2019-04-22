// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//#include "Components/ActorComponent.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"))
	ATank* debugTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
//	if (debugTank)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("AI Controlling: %s"), *(debugTank->GetName()))
//	}
//	else if (playerTank)
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