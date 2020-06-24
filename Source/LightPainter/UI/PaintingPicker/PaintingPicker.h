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
	// Components
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintingGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

	// State
	UPROPERTY(EditAnywhere)
	int32 CurrentPage = 0;

	int32 TotalPages = 0;

// ----------Custom Functions----------
public:
	void AddPainting();
	void EnableDeleteMode();
	void UpdateCurrentPage(int32 Offset);

protected:
private:
	void ClearSlots();
	void ClearDots();
	void Refresh();
	void RefreshSlots();
	void RefreshDots();
};
