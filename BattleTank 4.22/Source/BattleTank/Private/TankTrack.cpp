// Robert Hinds

#include "TankTrack.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

UTankTrack::UTankTrack()
{
	
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: I am hit"), *GetName())
		//Drive the tracks
		//Apply sideways force
		DriveTrack();
		ApplySidewaysForce();
		CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate the slippage speed
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	//work-out the required acceleration this frame to correct
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//Calculate and apply sideways for (F = m * a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide by two as there are two tracks.
																				  //TankRoot->AddForce(CorrectionForce);																		 									  
	TankRoot->AddForceAtLocation(CorrectionForce, GetComponentLocation());
}


//TODO refactor this to drivetrack (maybe different name if tank blueprint is still messed up) function and call new function from OnHit.
//TODO make member variable to hold throttle and use that in the yet to be implemented function.  as in lecture 235.
void UTankTrack::SetThrottle(float ThrottleAmt)
{
	
	//CurrentThrottle = ThrottleAmt;
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + ThrottleAmt, -1.f, 1.f);
	
}


void UTankTrack::DriveTrack()
{
	FVector ForceApplied = CurrentThrottle * TrackMaxDriveForce * GetForwardVector();
	FVector ForceLocation = GetComponentLocation();

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}