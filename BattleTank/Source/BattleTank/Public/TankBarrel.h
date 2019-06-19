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
		UFUNCTION()
			void ElevateBarrel(float DegreesPerSecond);

		
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.f; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDegrees = 40.f; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDegrees = 0.f; 
};
