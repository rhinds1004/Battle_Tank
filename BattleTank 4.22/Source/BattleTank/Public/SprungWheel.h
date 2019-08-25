// Robert HindsCopyright 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UStaticMeshComponent* Mass = nullptr;



	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UStaticMeshComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDrivePosStrength = 5000.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDriveVeloStrength = 2000.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDriveFoceLimit = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearMotionZLimit = 50.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
