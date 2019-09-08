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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	/*
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class USphereComponent* Axle = nullptr;
*/
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UStaticMeshComponent* Axle = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UPhysicsConstraintComponent* MassAxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDrivePosStrength = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDriveVeloStrength = 200.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearDriveFoceLimit = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		float LinearMotionZLimit = 50.f;


private:
	void SetupConstraint();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
		float TotalForceMagnitudeThisFrame = 0.f;

	void ApplyForce();
};
