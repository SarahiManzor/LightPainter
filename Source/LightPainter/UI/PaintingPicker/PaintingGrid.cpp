// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "PaintingGridCard.h"
#include "PaginationDots.h"

void UPaintingGrid::AddPainting(int32 GridIndex, FString SlotName)
{
	if (PaintingGrid)
	{
		UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(GridIndex));
		if (SizeBox)
		{
			SizeBox->AddChild(NewWidget);
			NewWidget->SetSlotName(SlotName);
		}
	}
}

void UPaintingGrid::ClearPaintings()
{
	if (PaintingGrid)
	{
		for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); i++)
		{
			USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
			SizeBox->ClearChildren();
		}
	}
}

void UPaintingGrid::ClearDots()
{
	if (PaginationBox)
	{
		PaginationBox->ClearChildren();
	}
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (PaginationBox)
	{
		UPaginationDots* NewWidget = CreateWidget<UPaginationDots>(GetWorld(), PaginationDotClass);
		NewWidget->SetActive(Active);

		UHorizontalBoxSlot* BoxSlot = PaginationBox->AddChildToHorizontalBox(NewWidget);
		BoxSlot->SetPadding(FMargin(8.0, 0.0));
	}
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid ? PaintingGrid->GetChildrenCount() : 0;
}
