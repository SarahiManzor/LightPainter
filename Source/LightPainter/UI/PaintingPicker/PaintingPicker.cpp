#include "PaintingPicker.h" 
#include "Components/WidgetComponent.h"
#include "PaintingGrid.h"
#include "ActionBar.h"
#include "../../Saving/PainterSaveGameIndex.h"
#include "../../Saving/PainterSaveGame.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}

void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	RefreshSlots();
	
	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame* SaveGame = UPainterSaveGame::Create();

	RefreshSlots();
}

void APaintingPicker::EnableDeleteMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Delete mode enabled."));
	ClearSlots();
}

void APaintingPicker::ClearSlots()
{
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		Grid->ClearPaintings();
	}
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		TArray<FString> Names = UPainterSaveGameIndex::Load()->GetSlotNames();
		for (int32 i = 0; i < Names.Num(); i++)
		{
			Grid->AddPainting(i, Names[i]);
		}
	}
}

