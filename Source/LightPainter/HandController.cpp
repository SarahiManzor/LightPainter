#include "HandController.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Stroke.h"

AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStroke)
	{
		CurrentStroke->Update(GetActorLocation() + GetActorForwardVector() * 5.0);
	}
}

void AHandController::TriggerDown()
{
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

void AHandController::TriggerUp()
{
	if (CurrentStroke)
	{
		CurrentStroke = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing stroke reference on hand controller"));
	}
}

