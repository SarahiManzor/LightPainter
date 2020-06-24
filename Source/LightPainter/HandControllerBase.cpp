#include "HandControllerBase.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Stroke.h"

AHandControllerBase::AHandControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetShowDeviceModel(true);
}

void AHandControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHandControllerBase::TriggerDown()
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger down"));
}

void AHandControllerBase::TriggerUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger up"));
}

void AHandControllerBase::SetTrackingSource(EControllerHand Hand)
{
	MotionController->SetTrackingSource(Hand);
}

