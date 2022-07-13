// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	
	initLoc = GetOwner()->GetActorLocation();
	currLoc = initLoc;
	targetLoc = initLoc + moveOffset;
	// ...
	speed = FVector::Distance(initLoc, targetLoc) / moveTime;

	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(shouldMove)
	{
		move(targetLoc, DeltaTime);
		
	}
	else
	{
		move(initLoc, DeltaTime);
	}
	
	
}

void UMover::SetShouldMove(bool newShouldMove)
{
	this->shouldMove = newShouldMove;
}

void UMover::move(FVector to, float DeltaTime)
{
	currLoc = GetOwner()->GetActorLocation();

	FVector newLoc = FMath::VInterpConstantTo( currLoc, to, DeltaTime, speed);

	GetOwner()->SetActorLocation(newLoc);
}
