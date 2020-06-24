#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "HandControllerBase.h"
#include "Components/InputComponent.h" 
#include "Saving/PainterSaveGame.h" 
#include "Kismet/GameplayStatics.h" 
#include "Stroke.h" 
#include "PaintingGameMode.h" 
#include "UI/PaintingPicker/PaintingPicker.h" 

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

	if (RightHandController)
	{
		RightHandControllerBase = GetWorld()->SpawnActor<AHandControllerBase>(RightHandController);
		RightHandControllerBase->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandControllerBase->SetOwner(this);
		RightHandControllerBase->SetTrackingSource(EControllerHand::Right);
	}

	if (LeftHandController)
	{
		LeftHandControllerBase = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandController);
		LeftHandControllerBase->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandControllerBase->SetOwner(this);
		LeftHandControllerBase->SetTrackingSource(EControllerHand::Left);
	}
}

void AVRPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerDown);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerUp);
	PlayerInputComponent->BindAction(FName("Clear"), IE_Released, this, &AVRPawn::Clear);
	PlayerInputComponent->BindAxis(FName("RightControllerThumbstickRight"), this, &AVRPawn::PaginateRightAxisInput);
}

void AVRPawn::RightTriggerDown()
{
	if (RightHandControllerBase)
	{
		RightHandControllerBase->TriggerDown();
	}
}

void AVRPawn::RightTriggerUp()
{
	if (RightHandControllerBase)
	{
		RightHandControllerBase->TriggerUp();
	}
}

void AVRPawn::PaginateRightAxisInput(float Value)
{
	int32 Input = Value > 0.5 ? 1 : Value < -0.5 ? -1 : 0;
	if (Input != 0 && Input != LastInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input: %i"), Input);
		UpdateCurrentPage(Input);
	}
	LastInput = Input;
}

void AVRPawn::UpdateCurrentPage(float Offset)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaintingPicker::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		APaintingPicker* Picker = Cast<APaintingPicker>(Actor);
		if (Picker)
		{
			Picker->UpdateCurrentPage(Offset);
		}
	}
}

void AVRPawn::Clear()
{
	int32 actorCount = 0;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStroke::StaticClass(), FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("Deleted %i"), FoundActors.Num());
	for (AActor* Stroke : FoundActors)
	{
		Stroke->Destroy();
	}
}



