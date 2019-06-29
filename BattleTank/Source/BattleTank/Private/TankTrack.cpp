// Robert Hinds

#include "TankTrack.h"

void UTankTrack::SetThrottle(float ThrottleAmt)
{
	Throttle = ThrottleAmt;
	UE_LOG(LogTemp, Warning, TEXT("%s value: %f"), *(this->GetName()), ThrottleAmt);
}
