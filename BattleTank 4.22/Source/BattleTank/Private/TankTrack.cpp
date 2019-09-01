// Robert Hinds

#include "TankTrack.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"

UTankTrack::UTankTrack()
{
	
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> MySceneComponents;
	GetChildrenComponents(true, MySceneComponents);
	TArray<ASprungWheel*> MyWheels;
	ASprungWheel* MyWheel;
	for (USceneComponent* MyScenseComponent : MySceneComponents)
	{
		UPhysicsConstraintComponent* MyConstraintWheel = Cast<UPhysicsConstraintComponent>(MyScenseComponent);
		if (MyConstraintWheel)
		{
			MyWheel = Cast<ASprungWheel>(MyConstraintWheel->GetOwner());
			if(MyWheel)
			MyWheels.Add(MyWheel);
		}
	}
	return TArray<ASprungWheel*>(MyWheels);
}

void UTankTrack::SetThrottle(float ThrottleAmt)
{
	float CurrentThrottle = FMath::Clamp<float>(ThrottleAmt, -1.f, 1.f);
	DriveTrack(CurrentThrottle);
}


void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDriveForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}