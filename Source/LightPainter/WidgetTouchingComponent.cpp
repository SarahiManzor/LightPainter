// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTouchingComponent.h"

UWidgetTouchingComponent::UWidgetTouchingComponent()
{
	bIsClicked = false;
}

void UWidgetTouchingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsOverInteractableWidget() && !bIsClicked)
	{
		PressPointerKey(EKeys::LeftMouseButton);
		bIsClicked = true;
	}
	else if (!IsOverInteractableWidget() && bIsClicked)
	{
		ReleasePointerKey(EKeys::LeftMouseButton);
		bIsClicked = false;
	}	
}
