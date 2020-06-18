#include "PaintBrushHandController.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Stroke.h"

APaintBrushHandController::APaintBrushHandController()
{
}

void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		CurrentStroke->Update(GetActorLocation() + GetActorForwardVector() * 5.0);
	}
}

void APaintBrushHandController::TriggerDown()
{
	Super::TriggerDown();
	if (Stroke)
	{
		FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 5.0f;
		CurrentStroke = GetWorld()->SpawnActor<AStroke>(Stroke, StartLocation, FRotator::ZeroRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing stroke reference on hand controller"));
	}
}

void APaintBrushHandController::TriggerUp()
{
	Super::TriggerUp();
	if (CurrentStroke)
	{
		CurrentStroke = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing stroke reference on hand controller"));
	}
}

