// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"


//Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//ControlledTank = Cast<ATank>(GetPawn());
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		
	}
}
void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank) || !ensure(AimingComponent)) { return; }
	
		//Move to player
		MoveToActor(PlayerTank, AcceptanceRadius); //check radius is in CM comes from Unreal Engines's AI pathfinding which is accessible due to inheriting from AI Controller
		//Aim towards player	
		AimingComponent->AimAtTarget(PlayerTank->GetActorLocation(), AimingComponent->ProjectileLaunchSpeed);
		//TODO only fire when barrel is pointed at player

		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	
}

void ATankAIController::OnTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("AI Tank died!"))
		GetPawn()->DetachFromControllerPendingDestroy();
}