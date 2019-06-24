// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed, and +1 is max up movement
		UFUNCTION()
			void ElevateBarrel(float RelativeSpeed);

		
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5.f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationInDegrees = 40.f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationInDegrees = 0.f; 
};
