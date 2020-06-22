// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBar.h"
#include "Components/Button.h"
#include "PaintingPicker.h"

bool UActionBar::Initialize()
{
	if (!Super::Initialize()) return false;

	if (AddButton)
	{
		AddButton->OnClicked.AddDynamic(this, &UActionBar::Add);
	}
	if (DeleteButton)
	{
		DeleteButton->OnClicked.AddDynamic(this, &UActionBar::Delete);
	}

	return true;
}

void UActionBar::SetParentPicker(APaintingPicker* NewPicker)
{
	PaintingPicker = NewPicker;
}

void UActionBar::Add()
{
	if (PaintingPicker)
	{
		PaintingPicker->AddPainting();
	}
}

void UActionBar::Delete()
{
	if (PaintingPicker)
	{
		PaintingPicker->EnableDeleteMode();
	}
}

