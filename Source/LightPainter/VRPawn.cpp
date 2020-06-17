#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "HandController.h"
#include "Components/InputComponent.h" 
#include "Saving/PainterSaveGame.h" 

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
	}

	UPainterSaveGame::Create()->Save();
}

void AVRPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerDown);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerUp);
}

void AVRPawn::RightTriggerDown()
{
	if (RightHandController)
	{
		RightHandController->TriggerDown();
	}
}

void AVRPawn::RightTriggerUp()
{
	if (RightHandController)
	{
		RightHandController->TriggerUp();
	}
}



