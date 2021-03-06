// Robert HindsCopyright 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	UFUNCTION(BlueprintPure, Category = "SpawnPoint Actor")
		AActor* GetSpawnedActor() const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<class AActor> SpawnClass;
	
private:
	UPROPERTY()
	AActor* SpawnedActor = nullptr;
		
};
