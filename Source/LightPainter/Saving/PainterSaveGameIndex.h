// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGameIndex.generated.h"

class UPainterSaveGame;

UCLASS()
class LIGHTPAINTER_API UPainterSaveGameIndex : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGameIndex* Load();
	bool Save();

	void AddSaveGame(UPainterSaveGame* SaveGame);
	TArray<FString> GetSlotNames() const;

private:
	UPROPERTY()
	TArray<FString> SaveGames;
};
