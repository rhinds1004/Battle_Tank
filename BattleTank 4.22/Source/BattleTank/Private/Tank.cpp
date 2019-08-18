// Copyright Robert Hinds

#include "Tank.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"

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
	float DamageTaken = 0.f;
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f"), DamageAmount) //TODO remove this and add logic to change health.
	
	return DamageTaken;
}