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
		class UPhysicsConstraintComponent* Spring = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
