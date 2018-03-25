// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "openDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UopenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UopenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:	
	
	UPROPERTY(editAnywhere)
	float TriggerMass = 30.f;

	UPROPERTY(editAnywhere)
	ATriggerVolume* plate = nullptr;	
	
	AActor * myOwner = nullptr;

	float getTotalActorsMass();
};
