// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "UIPointerHandControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API AUIPointerHandControllerBase : public AHandControllerBase
{
	GENERATED_BODY()


		// ----------Base Functions----------
public:
	AUIPointerHandControllerBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ----------Variables----------
public:
protected:
private:

	// ----------Custom Functions----------
public:
	virtual void TriggerDown() override;
	virtual void TriggerUp() override;
protected:
private:
	
};

