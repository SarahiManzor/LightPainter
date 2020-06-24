// Fill out your copyright notice in the Description page of Project Settings.


#include "PaletteMenuHandController.h"
#include "Components/WidgetComponent.h"

APaletteMenuHandController::APaletteMenuHandController()
{
	PaletteMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaletteMenu"));
	PaletteMenu->SetupAttachment(GetRootComponent());
}
