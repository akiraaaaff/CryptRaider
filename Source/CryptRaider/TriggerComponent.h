// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Mover.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTriggerComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Blueprint callable function which sets the mover component.
	UFUNCTION(BlueprintCallable)
	void setMover(UMover* mover);
	
	
	// Tag that actor must have to trigger mover.
	UPROPERTY(EditAnywhere)
	FName unlockTag;
	
private:
	// Mover associated with a trigger (set up in blueprint).
	UMover* mover;
	// Returns a pointer to the unlocking actor.
	AActor* GetUnlockingActor() const;
};
