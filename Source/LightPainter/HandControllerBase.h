// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandControllerBase.generated.h"

class UMotionControllerComponent;

UCLASS()
class LIGHTPAINTER_API AHandControllerBase : public AActor
{
	GENERATED_BODY()


// ----------Base Functions----------
public:
	AHandControllerBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ----------Variables----------
public:
protected:
private:
	// Components
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionController;

	// ----------Custom Functions----------
public:
	virtual void TriggerDown();
	virtual void TriggerUp();
protected:
private:

};
