// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandControllerBase.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Stroke.h"
#include "Components/WidgetInteractionComponent.h"
#include "InputCoreTypes.h"

AUIPointerHandControllerBase::AUIPointerHandControllerBase()
{
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(GetRootComponent());
}

void AUIPointerHandControllerBase::BeginPlay()
{
	Super::BeginPlay();
	WidgetInteractionComponent->bShowDebug = true;
}

void AUIPointerHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIPointerHandControllerBase::TriggerDown()
{
	Super::TriggerDown();
	WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandControllerBase::TriggerUp()
{
	Super::TriggerUp();
	WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}

