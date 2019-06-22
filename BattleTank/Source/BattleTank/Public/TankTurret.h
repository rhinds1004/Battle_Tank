// Robert Hinds

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
		void RotateTurret(float RelativeSpeed);
	
		UPROPERTY(EditAnywhere, Category = Setup)
			float MaxRotationSpeed = 10.f;
	
};
