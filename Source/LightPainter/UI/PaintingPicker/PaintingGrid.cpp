// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"
#include "PaintingGridCard.h"

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
