// Robert HindsCopyright 2019


#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	MassWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, LinearMotionZLimit);
	MassWheelConstraint->SetLinearDriveParams(LinearDrivePosStrength, LinearDriveVeloStrength, LinearDriveFoceLimit);
	MassWheelConstraint->SetLinearPositionDrive(false, false, true);
	MassWheelConstraint->SetLinearVelocityDrive(false, false, true);



	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetSimulatePhysics(true);
	Mass->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetupAttachment(MassWheelConstraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent %s"), *GetParentActor()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent is Null"));
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

