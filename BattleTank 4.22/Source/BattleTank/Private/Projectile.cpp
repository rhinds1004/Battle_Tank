// Robert Hinds

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject <UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(CollisionMesh);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovementComponent->bAutoActivate = false;
	InitialLifeSpan = 7.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/// The forward vector is the projectiles's forward vector. This works because when the projectile 
/// was spawned we set the location to be the socket owned by the barrel. Therefore the 
/// projectile will be facing the same direction as the barrel.
/*
 It is assumed that the projectile is facing the correct direction when this function is called.
*/
void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); 
	ProjectileMovementComponent->Activate();
}