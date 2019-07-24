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

	UFUNCTION(BlueprintCallable, category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet );

	UFUNCTION(BlueprintCallable, category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, category = "Input")
	void IntendMoveRight(float Throw);
	
	UFUNCTION(BlueprintCallable, category = "Input")
	void SetLeftTrackThrottle(float Throw);

	UFUNCTION(BlueprintCallable, category = "Input")
	void SetRightTrackThrottle(float Throw);

protected:
	UTankMovementComponent();
	virtual void BeginPlay() override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	//Called from the pathfinding logic by the AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
