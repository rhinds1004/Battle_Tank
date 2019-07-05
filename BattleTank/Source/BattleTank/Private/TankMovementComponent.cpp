// Robert Hinds

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Tank.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if(ensure(LeftTrackToSet) && ensure(RightTrackToSet))
	{ 
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	}
	
	//TODO REmove this workaround. Needed because the reference to the tank movement component is getting nulled in the tank class after this function returns. Need to find out why.
	ATank* OwnerTank = Cast<ATank>(GetOwner());
	OwnerTank->SetMyMoveComp(this);	
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Indend move forward: %f"), Throw);
	if (!LeftTrack|| !RightTrack) { return; }
	
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
}

UTankTrack * UTankMovementComponent::GetLeftTrack()
{
	return LeftTrack;
}

UTankTrack * UTankMovementComponent::GetRightTrack()
{
	return RightTrack;
}

