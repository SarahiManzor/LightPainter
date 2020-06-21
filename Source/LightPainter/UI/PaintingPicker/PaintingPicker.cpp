#include "PaintingPicker.h" 
#include "Components/WidgetComponent.h"
#include "PaintingGrid.h"
#include "../../Saving/PainterSaveGameIndex.h"

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

	UPaintingGrid* Grid = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (Grid)
	{
		TArray<FString> Names = UPainterSaveGameIndex::Load()->GetSlotNames();
		for (int32 i = 0; i < Names.Num(); i++)
		{
			Grid->AddPainting(i);
		}
	}
}

