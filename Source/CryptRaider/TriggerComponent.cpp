// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent(){

	PrimaryComponentTick.bCanEverTick = true;
	this->unlockTag = "";

}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if mover is set then do the logic.
	if(mover){
		AActor* unlockingActor = GetUnlockingActor();
		// if appriate actor overlaps the component then attach actor's root component to this component and tell mover to move.
		if(unlockingActor)
		{
			if(auto* component = Cast<UPrimitiveComponent>(unlockingActor->GetRootComponent()))
			{
				component->SetSimulatePhysics(false);
				component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			}
			mover->SetShouldMove(true);
		} 
		else
		{
			mover->SetShouldMove(false);
		}
	}


}

AActor* UTriggerComponent::GetUnlockingActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	
	// Find appropriate unlocking actor with an approriate tag and return it.
	for(auto& actor : actors){
		if(actor->ActorHasTag(this->unlockTag) && !actor->ActorHasTag("Grabbed")){
			return actor;
		}
	}

	// return nullptr otherwise.
	return nullptr;

}

void UTriggerComponent::setMover(UMover* newMover)
{
	this->mover = newMover;
}