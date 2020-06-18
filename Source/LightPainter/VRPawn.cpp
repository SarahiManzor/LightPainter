#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "HandController.h"
#include "Components/InputComponent.h" 
#include "Saving/PainterSaveGame.h" 
#include "Kismet/GameplayStatics.h" 
#include "Stroke.h" 

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
}

void AVRPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerDown);
	PlayerInputComponent->BindAction(FName("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerUp);
	PlayerInputComponent->BindAction(FName("Save"), IE_Released, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction(FName("Load"), IE_Released, this, &AVRPawn::Load);
	PlayerInputComponent->BindAction(FName("Clear"), IE_Released, this, &AVRPawn::Clear);
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

void AVRPawn::Save()
{
	UE_LOG(LogTemp, Warning, TEXT("Save"));
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	Painting->SerializeFromWorld(GetWorld());
	Painting->Save();
}

void AVRPawn::Load()
{
	UE_LOG(LogTemp, Warning, TEXT("Load"));
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
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



