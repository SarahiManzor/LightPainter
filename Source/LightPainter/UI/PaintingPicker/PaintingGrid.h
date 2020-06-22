// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGrid.generated.h"

class UUniformGridPanel;
class UUserWidget;
class UPaintingGridCard;

UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 GridIndex, FString SlotName);
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;
};
