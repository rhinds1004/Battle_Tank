// Robert Hinds

#include "TankTrack.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"

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
		USpawnPoint* MySpawnPoint = Cast<USpawnPoint>(MyScenseComponent);
		if (MySpawnPoint)
		{
			MyWheel = Cast<ASprungWheel>(MySpawnPoint->GetSpawnedActor());
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
	
	float LineTraceDistance = 100.f;
	FVector Start;
	FVector End;
	int8 WheelHitCount = 0;
	float ForceApplied = CurrentThrottle * TrackMaxDriveForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	

	// additional trace parameters
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	//TraceParams.bTraceComplex = true;
	//TraceParams.bReturnPhysicalMaterial = true;
	//Re-initialize hit info
	FHitResult HitDetails = FHitResult(ForceInit);
	bool bIsHit = false;

	for (ASprungWheel* Wheel : Wheels)
	{
		bIsHit = false;
		if (Wheel->GetWheel())
		{
			Start = Wheel->GetWheel()->GetComponentLocation();
			//Start.Z -= Wheel->GetWheel()->GetScaledSphereRadius();
			End = Start;
			//End.Z -= 7.f; 
			End.Z -= Wheel->GetWheel()->GetScaledSphereRadius();
			bIsHit = GetWorld()->LineTraceSingleByChannel(
				HitDetails,      // FHitResult object that will be populated with hit info
				Start,      // starting position
				End,        // end position
				ECC_WorldDynamic,  // collision channel 
				TraceParams      // additional trace settings
			);
			if (bIsHit)
			{
				WheelHitCount += 1;
				//TODO remove after I am sure its working.
				//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);
				//UE_LOG(LogTemp, Warning, TEXT("Start: %s , End: %s "), *Start.ToCompactString(), *End.ToCompactString());
			}
			else
			{
				//TODO remove after I am sure its working.
				//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.f, ECC_WorldStatic, 1.f);
			}
		}
	}

	//float ForcePerWheel = ForceApplied / Wheels.Num();
	float ForcePerWheel = 0.f;
		if (WheelHitCount > 0)
		{
			ForcePerWheel = ForceApplied / WheelHitCount;
		}
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}