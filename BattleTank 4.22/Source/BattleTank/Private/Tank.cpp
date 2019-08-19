// Copyright Robert Hinds

#include "Tank.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"

float ATank::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP begin Play to run!
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageTaken = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageTaken;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageTaken;
}