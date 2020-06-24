// Fill out your copyright notice in the Description page of Project Settings.


#include "PaginationDots.h"
#include "Components/Image.h"

void UPaginationDots::SetActive(bool Active)
{
	if (Dot)
	{
		Dot->RenderOpacity = Active ? 1.0 : 0.4;
	}
}