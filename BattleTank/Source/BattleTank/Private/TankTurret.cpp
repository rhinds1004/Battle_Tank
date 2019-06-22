// Robert Hinds

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	auto RotationChange = RelativeSpeed * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
