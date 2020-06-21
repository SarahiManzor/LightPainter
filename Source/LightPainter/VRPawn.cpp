#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "HandControllerBase.h"
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

	if (HandControllerBaseClass)
	{
		RightHandControllerBase = GetWorld()->SpawnActor<AHandControllerBase>(HandControllerBaseClass);
		RightHandControllerBase->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandControllerBase->SetOwner(this);
	}

	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	if (Painting)
	{
		CurrentSlotName = Painting->GetSlotName();
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

void AVRPawn::Save()
{
	UE_LOG(LogTemp, Warning, TEXT("Save"));
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void AVRPawn::Load()
{
	UE_LOG(LogTemp, Warning, TEXT("Load"));
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
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



