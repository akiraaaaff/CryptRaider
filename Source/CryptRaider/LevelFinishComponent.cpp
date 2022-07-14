// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFinishComponent.h"
#include "Kismet/GameplayStatics.h"


ULevelFinishComponent::ULevelFinishComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

}


void ULevelFinishComponent::BeginPlay()
{
    this->levelFinished = false;
}


void ULevelFinishComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

    AActor* desiredActor = GetDesiredActor();
    // If the desired component is not a nullptr, then process "level complete" state.
	if(desiredActor)
	{
        // Attach the root component of the actor to THIS component.
		if(auto* component = Cast<UPrimitiveComponent>(desiredActor->GetRootComponent()))
		{
			component->SetSimulatePhysics(false);
			component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		}
        // set flag to true to indicate level complete.
        levelFinished = true;
    } 

    // Start count down and open new level upon timer reaches 0, if level is complete.
    if(levelFinished)
    {
        if(timer>0)
        {
            timer -= DeltaTime;   
        } 
        else
        {
            UGameplayStatics::OpenLevel(GetWorld(), this->levelName);
        }
    }
}

AActor* ULevelFinishComponent::GetDesiredActor() const
{
    // Get array of overlapping actors.
	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	
    // Itterate through array of overlapping actors and return the actor, which should be in the "ungrabbed state".
    
    for(auto& actor : actors){
		if(actor->ActorHasTag(this->treasureName) && !actor->ActorHasTag("Grabbed")){ 
			return actor;
		}
	}
    // Return nullptr nothing overlaps it.
	return nullptr;

}