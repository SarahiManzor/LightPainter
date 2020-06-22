// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintingPicker.generated.h"

class UWidgetComponent;

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
	GENERATED_BODY()
	
// ----------Base Functions----------
public:
	APaintingPicker();

protected:
	virtual void BeginPlay() override;

public:

// ----------Variables----------
public:
protected:
private:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintingGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

// ----------Custom Functions----------
public:
	void AddPainting();
	void EnableDeleteMode();

protected:
private:
	void ClearSlots();
	void RefreshSlots();
};
