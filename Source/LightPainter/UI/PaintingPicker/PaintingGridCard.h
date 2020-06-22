// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGridCard.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class LIGHTPAINTER_API UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSlotName(FString NewName);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SlotName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* SlotButton;

	FString PaintingName;

private:
	UFUNCTION()
	void SlotButtonClicked();
};
