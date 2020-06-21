// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGameIndex.h"
#include "Kismet/GameplayStatics.h"
#include "PainterSaveGame.h"

UPainterSaveGameIndex* UPainterSaveGameIndex::Load() 
{
	UPainterSaveGameIndex* Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveGames"), 0));
	if (!Index)
	{
		Index = Cast<UPainterSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->Save();
	}
	return Index;
}

bool UPainterSaveGameIndex::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("SaveGames"), 0);
}

void UPainterSaveGameIndex::AddSaveGame(UPainterSaveGame* SaveGame)
{
	SaveGames.Add(SaveGame->GetSlotName());
}

TArray<FString> UPainterSaveGameIndex::GetSlotNames() const
{
	return SaveGames;
}

