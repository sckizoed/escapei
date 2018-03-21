// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab()
{
	auto hit = GetFirstPhysicsBodyInReach();
	auto componentToGab = hit.GetComponent();
	AActor* actorHit = hit.GetActor();

	if (actorHit) {

		physicsHandle->GrabComponent(
			componentToGab,
			NAME_None,
			componentToGab->GetOwner()->GetActorLocation(),
			true);

	}
}
void UGrabber::letGo()
{
	physicsHandle->ReleaseComponent();

}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	findPhysicshandleComp();
	findInputComp();

}
//finding physics handler
void UGrabber::findPhysicshandleComp() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Missing your Physics Handler class in the Object : %s"),
			*(GetOwner()->GetName()));
	}
}
//set up input
void UGrabber::findInputComp() {
	PlayerInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PlayerInput)
	{
		PlayerInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PlayerInput->BindAction("Grab", IE_Released, this, &UGrabber::letGo);
	}
	else {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Missing your playe input class in the Object : %s"),
			*(GetOwner()->GetName()));
	}
}


const FVector UGrabber::getEndTrace()
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	return (playerViewPointLocation + playerViewPointRotation.Vector() * reach);
}

const FVector UGrabber::getStartTrace()
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	return (playerViewPointLocation);
}



const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult lineTraceHit;

	FCollisionQueryParams traceParameter(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT lineTraceHit,
		getStartTrace(),
		getEndTrace(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameter
	);

	return lineTraceHit;
}




// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (physicsHandle->GrabbedComponent)
		physicsHandle->SetTargetLocation(getEndTrace());

}