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

	//How close ai tank can get to target
	UPROPERTY()
	float AcceptanceRadius = 3000.f;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* AimingComponent = nullptr;

public:
	virtual void BeginPlay() override;

};
