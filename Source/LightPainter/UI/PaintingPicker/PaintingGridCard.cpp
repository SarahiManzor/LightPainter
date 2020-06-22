// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridCard.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void UPaintingGridCard::SetSlotName(FString NewName)
{
	PaintingName = NewName;
	if (SlotName)
	{
		SlotName->SetText(FText::FromString(NewName));
	}

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UPaintingGridCard::SlotButtonClicked);
	}
}

void UPaintingGridCard::SlotButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName);
}
