// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving the tank tracks.
 */

//Forward Declarations
class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet );

	UFUNCTION(BlueprintCallable, category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, category = Input)
	void IntendMoveRight(float Throw);
	
	UFUNCTION()
		UTankTrack* GetLeftTrack();
	UFUNCTION()
		UTankTrack* GetRightTrack();


private:
		UTankTrack* LeftTrack = nullptr;
		UTankTrack* RightTrack = nullptr;
};
