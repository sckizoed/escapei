// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "openDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UopenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UopenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void openDoors();
	void closeDoors();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	UPROPERTY(editAnywhere)
	float OpenDoorDelay = 1.f;

	float LastTimeDoorOpen;

	UPROPERTY(visibleAnywhere)
	float openAngle = -70.f;

	UPROPERTY(editAnywhere)
	ATriggerVolume* plate;	
	
	AActor * myOwner;

	float getTotalActorsMass();
};
