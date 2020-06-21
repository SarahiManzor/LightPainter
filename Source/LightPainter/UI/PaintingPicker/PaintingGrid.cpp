// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 GridIndex)
{
	if (PaintingGrid)
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(GridIndex));
		if (SizeBox)
		{
			SizeBox->AddChild(NewWidget);
		}
	}
}