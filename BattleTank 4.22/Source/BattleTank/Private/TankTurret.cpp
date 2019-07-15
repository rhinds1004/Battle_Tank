// Robert Hinds

#include "TankTurret.h"

//TODO fix the fact it rotates all away around when it hits -180 degrees or 180. Do to how the orientation rotation calculation is done in tankaimingcomponent.
void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));	
}
