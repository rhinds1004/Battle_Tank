// Robert HindsCopyright 2019


#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassAxleConstraint);

	MassAxleConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassAxleConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MassAxleConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	MassAxleConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassAxleConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MassAxleConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, LinearMotionZLimit);
	MassAxleConstraint->SetLinearDriveParams(LinearDrivePosStrength, LinearDriveVeloStrength, LinearDriveFoceLimit);
	MassAxleConstraint->SetLinearPositionDrive(false, false, true);
	MassAxleConstraint->SetLinearVelocityDrive(false, false, true);


	/*
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetSimulatePhysics(true);
	Mass->SetupAttachment(MassAxleConstraint);
	*/


	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetSimulatePhysics(true);
	Axle->SetupAttachment(MassAxleConstraint);
	/*
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetSimulatePhysics(true);
	Axle->SetupAttachment(MassAxleConstraint);
	*/
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetupAttachment(Axle);

	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true); // turns on Generate on hits
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{

		TotalForceMagnitudeThisFrame = 0;
	}
	

	
}

void ASprungWheel::AddDrivingForce(float ForceMagnitudeToApply)
{
	TotalForceMagnitudeThisFrame += ForceMagnitudeToApply;
}

USphereComponent * ASprungWheel::GetWheel()
{
	return Wheel;
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

