// Robert Hinds

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "TankBarrel.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO does this component need to tick?

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	//TODO remove this condition check?
	if (BarrelToSet)
	{
		Barrel = BarrelToSet;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to set Barrel reference"))
	}
	
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//
void UTankAimingComponent::AimAtTarget(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	
	TArray<AActor *>ActorsToIgnore;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // getsocketlocation will return the component location if socket isn't found
	//TODO trace option always returns true if set to do not trace. If set to Tracefullpath solution and no solutions occur even when cursor is not moved.
	bool SuggestProjectileVelocityResult = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, HitLocation,
		LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::TraceFullPath,
		FCollisionResponseParams::DefaultResponseParam, ActorsToIgnore, false);
	if (SuggestProjectileVelocityResult)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
		UE_LOG(LogTemp, Warning, TEXT("at time %f Aim Solution Found"), GetWorld()->GetTimeSeconds());
	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("at time %f NO Aim Solution Found"), GetWorld()->GetTimeSeconds());
	
	}
	//if no solution do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/*
		Get where I want barrel to point in the world
		make the location relative to barrel
		move the xyz of the barrel using the relative vector calculated above
	*/

	auto BarrelRotation = Barrel->GetForwardVector().ToOrientationRotator();
	auto AimAsRotator = AimDirection.ToOrientationRotator();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	

	Barrel->ElevateBarrel(DeltaRotator.Pitch); 

}