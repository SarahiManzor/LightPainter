// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

class AStroke;

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AStroke> Class;

	UPROPERTY()
	TArray<FVector> ControlPoints;

	UPROPERTY()
	FVector Location;
};

class AStroke;

UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	bool Save();
	static UPainterSaveGame* Load(FString SlotName);

	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

	FString GetSlotName() const {return SlotName;}

private:
	void ClearWorld(UWorld* World);

private:
	// State
	UPROPERTY()
	TArray<FStrokeState> Strokes;

	UPROPERTY()
	FString SlotName;
};
