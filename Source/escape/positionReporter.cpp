// Fill out your copyright notice in the Description page of Project Settings.

#include "positionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UpositionReporter::UpositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UpositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString myname = GetOwner()->GetName();
	FString myposition = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at : %s "), *myname, *myposition);
	
}


// Called every frame
void UpositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

