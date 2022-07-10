// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...


	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if(physicsHandle == nullptr)
		return;
	
	FVector targetLoc = GetComponentLocation() + GetForwardVector() * HoldDistance;

	physicsHandle->SetTargetLocationAndRotation(targetLoc, GetComponentRotation()); 

}


void UGrabber::Release(){
		UE_LOG(LogTemp, Display, TEXT("Released"));
}


void UGrabber::Grab(){

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	
	if(physicsHandle == nullptr)
		return;



	FVector start = GetComponentLocation();

	FVector end = start + (GetForwardVector() * MaxGrabDistance);

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		start,
		end,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere
	);

	if(hasHit){
		// UE_LOG(LogTemp, Display, TEXT("Actor's name %s"), *hitResult.GetActor()->GetActorNameOrLabel());
		physicsHandle->GrabComponentAtLocationWithRotation(
			hitResult.GetComponent(),
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
		UE_LOG(LogTemp, Display, TEXT("Grabbed"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* res = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(res == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return res;
}
