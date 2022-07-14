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

	// Update location of the grabbed component (if it is grabbed).
	if(auto* handle = GetPhysicsHandle()){
		if(auto* grabbedComp = handle->GetGrabbedComponent()){
			FVector targetLoc = GetComponentLocation() + GetForwardVector() * HoldDistance;
			handle->SetTargetLocationAndRotation(targetLoc, GetComponentRotation());
		} 
	}

}


void UGrabber::Release(){

	

	if(auto* handle = GetPhysicsHandle()){
		// Release component if it is grabbed
		if(auto* grabbedComp = handle->GetGrabbedComponent()){
			grabbedComp->WakeAllRigidBodies();
			handle->ReleaseComponent();
			// Delete a tag upon releasing.
			auto& tags = grabbedComp->GetOwner()->Tags;
			if(tags.Contains("Grabbed")){
				tags.Remove("Grabbed");
			}
		}
	}
}


void UGrabber::Grab(){

	FHitResult hitResult;
	bool hasHit;
	
	GetGrabbableInReach(hasHit, hitResult);

	// If approapriate object was grabbed, process logic.
	if(hasHit){

		// Make hitcomponent component interactable.
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();

		
		auto* hitActor = hitResult.GetActor();
		auto& tags = hitActor->Tags;
		
		// Add Grabbed tag to the object.
		if(!tags.Contains("Grabbed")){
			tags.Add("Grabbed");
		}

		// Detach it from root scene component.
		hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);


		// Grab and drag component.
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
			hitResult.GetComponent(),
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
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

void UGrabber::GetGrabbableInReach(bool& hasHit, FHitResult& hitResult) const
{
	
	if(auto* handle = GetPhysicsHandle())
	{
		// Parameters required for sweep function.

		FVector start = GetComponentLocation();

		FVector end = start + (GetForwardVector() * MaxGrabDistance);

		FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

		// Perform sweep.
		hasHit = GetWorld()->SweepSingleByChannel(
			hitResult,
			start,
			end,
			FQuat::Identity,				// No rotation.
			ECC_GameTraceChannel2,			// Grabbed Trace Channel.
			sphere
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	


}
