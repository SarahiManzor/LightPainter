// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaginationDots.generated.h"

class UImage;

UCLASS()
class LIGHTPAINTER_API UPaginationDots : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActive(bool Active);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UImage* Dot;
};
