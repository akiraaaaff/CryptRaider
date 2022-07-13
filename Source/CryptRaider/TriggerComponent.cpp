// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent(){

	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Begin!"));
	this->unlockTag = "";

}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Begin!"));

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(mover){
		AActor* unlockingActor = GetUnlockingActor();
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
	// UE_LOG(LogTemp, Display, TEXT("I am %d"), actors.Num());


}

AActor* UTriggerComponent::GetUnlockingActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	for(auto& actor : actors){
		if(actor->ActorHasTag(this->unlockTag) && !actor->ActorHasTag("Grabbed")){
			return actor;
		}
	}
	return nullptr;

}

void UTriggerComponent::setMover(UMover* newMover)
{
	this->mover = newMover;
}