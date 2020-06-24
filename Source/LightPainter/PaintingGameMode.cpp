// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/PainterSaveGame.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
}

void APaintingGameMode::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (!Painting)
	{
		Painting = UPainterSaveGame::Create();
		if (Painting)
		{
			SlotName = Painting->GetSlotName();
		}
	}

	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void APaintingGameMode::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
	}
}

void APaintingGameMode::SaveAndQuit()
{
	Save();
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"), true);
}

