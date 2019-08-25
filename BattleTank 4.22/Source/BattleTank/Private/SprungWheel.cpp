// Robert HindsCopyright 2019


#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	
	Mass->SetSimulatePhysics(true);
	SetRootComponent(Mass);
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);

	
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));


	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, LinearMotionZLimit);
	MassWheelConstraint->SetLinearDriveParams(LinearDrivePosStrength, LinearDriveVeloStrength, LinearDriveFoceLimit);
	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);

	MassWheelConstraint->SetupAttachment(Mass);
	Wheel->SetupAttachment(Mass);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

