// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "LevelFinishComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API ULevelFinishComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	ULevelFinishComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// Treasure tag which is required to reach "level complete" state
	UPROPERTY(EditAnywhere)
	FName treasureName;

	// Level to be loaded upon completion of current level.
	UPROPERTY(EditAnywhere)
	FName levelName;

	// Time period between completion of level and loading the new level.
	UPROPERTY(EditAnywhere)
	float timer;
	
private:
	
	// Function which returns a right actor for "level complete" state if it overlaps the component.
	AActor* ULevelFinishComponent::GetDesiredActor() const;

	// Flag which denotes whether the level is finished or not.
	bool levelFinished;
};
