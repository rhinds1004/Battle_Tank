// Robert Hinds

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankTrack::SetThrottle(float ThrottleAmt)
{
	//ThrottleAmt = FMath::Clamp<float>(ThrottleAmt, -1.f, 1.f);
	FVector ForceApplied = ThrottleAmt * TrackMaxDriveForce * GetForwardVector();
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}
