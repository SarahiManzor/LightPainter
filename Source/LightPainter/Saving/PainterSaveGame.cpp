// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "../Stroke.h"
#include "EngineUtils.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0);
}

UPainterSaveGame* UPainterSaveGame::Load()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Test"), 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	// Clear array
	Strokes.Empty();
	// Iterate over all strokes
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++ StrokeItr)
	{
		// Serialize
		// Store class type
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	// Clear world
	ClearWorld(World);

	// For all strokes
	for (FStrokeState StrokeState : Strokes)
	{
		// Spawn strokes of that type
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	int32 actorCount = 0;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, AStroke::StaticClass(), FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("Deleted %i"), FoundActors.Num());
	for (AActor* Stroke : FoundActors)
	{
		Stroke->Destroy();
	}
}