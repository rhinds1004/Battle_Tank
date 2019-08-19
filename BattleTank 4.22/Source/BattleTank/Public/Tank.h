// Copyright Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Delegate.h"
#include "Tank.generated.h"

/*
*
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankBroadcast);



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	
	//Returns Current Health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(BlueprintAssignable, Category = "Setup")
	FTankBroadcast OnDeath;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth = MaxHealth;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
