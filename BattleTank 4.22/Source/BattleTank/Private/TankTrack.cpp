// Robert Hinds

#include "TankTrack.h"



void UTankTrack::SetThrottle(float ThrottleAmt)
{
	//ThrottleAmt = FMath::Clamp<float>(ThrottleAmt, -1.f, 1.f);
	auto ForceApplied = ThrottleAmt * TrackMaxDriveForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}
