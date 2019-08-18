// Copyright Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/*
*
*/

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

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
