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

	Refresh();
	
	UActionBar* ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}
}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame* SaveGame = UPainterSaveGame::Create();

	Refresh();
}

void APaintingPicker::EnableDeleteMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Delete mode enabled."));
	ClearSlots();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, TotalPages - 1);
	Refresh();
}

void APaintingPicker::ClearSlots()
{
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		Grid->ClearPaintings();
	}
}

void APaintingPicker::ClearDots()
{
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		Grid->ClearDots();
	}
}

void APaintingPicker::Refresh()
{
	RefreshSlots();
	RefreshDots();
}

void APaintingPicker::RefreshSlots()
{
	ClearSlots();
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		TArray<FString> Names = UPainterSaveGameIndex::Load()->GetSlotNames();
		int32 Offset = CurrentPage * Grid->GetNumberOfSlots();
		for (int32 i = 0; i < Names.Num() - Offset; i++)
		{
			Grid->AddPainting(i, Names[i + Offset]);
		}
	}
}

void APaintingPicker::RefreshDots()
{
	ClearDots();
	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		TArray<FString> Names = UPainterSaveGameIndex::Load()->GetSlotNames();
		TotalPages = FMath::CeilToInt((float)Names.Num() / Grid->GetNumberOfSlots());
		for (int32 i = 0; i < TotalPages; i++)
		{
			Grid->AddPaginationDot(i == CurrentPage);
		}
	}
}

