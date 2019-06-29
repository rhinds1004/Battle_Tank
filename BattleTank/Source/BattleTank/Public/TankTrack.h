// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maxiumum driving force, and apply forces to the track
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	float Throttle = 0;


public:
		UFUNCTION(BlueprintCallable, category = Input)
		void SetThrottle(float ThrottleAmt);
	
	
};
