// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable, category = Input)
		void IntendMoveForward(float Throw);
	
	
};