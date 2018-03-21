// Fill out your copyright notice in the Description page of Project Settings.


#include "openDoor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#define OUT

//#include "Engine.h"

// Sets default values for this component's properties
UopenDoor::UopenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UopenDoor::BeginPlay()
{
	Super::BeginPlay();
	myOwner = GetOwner();
}

void UopenDoor::openDoors()
{
	myOwner->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

void UopenDoor::closeDoors()
{
	myOwner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UopenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (getTotalActorsMass() > 30)
	{
		openDoors();
		LastTimeDoorOpen = GetWorld()->GetTimeSeconds();
	}

	if ((GetWorld()->GetTimeSeconds() - LastTimeDoorOpen) > OpenDoorDelay) {
		closeDoors();
	}


}

float UopenDoor::getTotalActorsMass() {
	
	float totalMass = 0.f;
	TArray <AActor*> overlappingActors;

	plate->GetOverlappingActors(OUT overlappingActors);

	for (const auto& actori : overlappingActors) {
		totalMass += actori->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *(actori->GetName()));
	}

	return totalMass;
}

