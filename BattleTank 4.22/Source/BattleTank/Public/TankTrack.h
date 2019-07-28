// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"



/**
 * TankTrack is used to set maxiumum driving force, and apply forces to the track
 */


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UTankTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


public:

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, category = "Input")
	void SetThrottle(float ThrottleAmt);

	UFUNCTION()
	void DriveTrack();

	UPROPERTY()
		float CurrentThrottle = 0;

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	float TrackMaxDriveForce = 400000;  //Assume tank weight is 40 and 1 g accelleration
	
	
};
