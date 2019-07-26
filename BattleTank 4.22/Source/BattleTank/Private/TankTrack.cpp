// Robert Hinds

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//calculate the slippage speed
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	//work-out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//Calculate and apply sideways for (F = m * a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide by two as there are two tracks.
	//TankRoot->AddForce(CorrectionForce);																		 									  
	TankRoot->AddForceAtLocation(CorrectionForce, GetComponentLocation());
}

void UTankTrack::SetThrottle(float ThrottleAmt)
{
	//ThrottleAmt = FMath::Clamp<float>(ThrottleAmt, -1.f, 1.f);
	FVector ForceApplied = ThrottleAmt * TrackMaxDriveForce * GetForwardVector();
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}
