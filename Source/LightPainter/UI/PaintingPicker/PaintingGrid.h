// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGrid.generated.h"

class UUniformGridPanel;
class UUserWidget;
class UPaintingGridCard;
class UHorizontalBox;
class UPaginationDots;

UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 GridIndex, FString SlotName);
	void ClearPaintings();
	void ClearDots();
	void AddPaginationDot(bool Active);
	int32 GetNumberOfSlots() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PaginationBox;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaginationDots> PaginationDotClass;

};
