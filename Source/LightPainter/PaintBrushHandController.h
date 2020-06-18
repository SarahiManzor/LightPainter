// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"

class UMotionControllerComponent;
class AStroke;

UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()


// ----------Base Functions----------
public:	
	APaintBrushHandController();

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

	// State
	UPROPERTY()
	AStroke* CurrentStroke;

// ----------Custom Functions----------
public:
	virtual void TriggerDown() override;
	virtual void TriggerUp() override;
protected:
private:
};
