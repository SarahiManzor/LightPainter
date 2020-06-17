// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

class UMotionControllerComponent;
class AStroke;

UCLASS()
class LIGHTPAINTER_API AHandController : public AActor
{
	GENERATED_BODY()


// ----------Base Functions----------
public:	
	AHandController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// ----------Variables----------
public:
protected:
private:
	// Config
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> Stroke;

	// Components
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionController;

	// State
	UPROPERTY()
	AStroke* CurrentStroke;

// ----------Custom Functions----------
public:
	void TriggerDown();
	void TriggerUp();
protected:
private:
};
