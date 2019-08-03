// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void Tick(float DeltaTime) override;



protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* AimingComponent = nullptr;

	//How close ai tank can get to target
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000.f;

public:
	virtual void BeginPlay() override;

};
