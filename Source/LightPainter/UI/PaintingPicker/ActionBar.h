// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBar.generated.h"

class UButton;
class APaintingPicker;

UCLASS()
class LIGHTPAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetParentPicker(APaintingPicker* NewPicker);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* DeleteButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* AddButton;

private:
	UFUNCTION()
	void Add();

	UFUNCTION()
	void Delete();

	UPROPERTY()
	APaintingPicker* PaintingPicker;
};
