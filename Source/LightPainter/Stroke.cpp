// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h" 

// Sets default values
AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponents"));
	InstancedStaticMeshComponent->SetupAttachment(Root);

	DefaultScale = FVector::OneVector;
}

void AStroke::BeginPlay()
{
	PreviousCursorLocation = GetActorLocation();
	if (!InstancedStaticMeshComponent->GetStaticMesh())
	{
		InstancedStaticMeshComponent->SetStaticMesh(SplineMesh);
	}
	if (!InstancedStaticMeshComponent->GetMaterial(0))
	{
		InstancedStaticMeshComponent->SetMaterial(0, SplineMaterial);
	}
}

void AStroke::Update(FVector CursorLocation)
{
	FTransform InstanceTransform;

	InstanceTransform.SetLocation(GetSegmentPosition(CursorLocation));
	InstanceTransform.SetScale3D(GetSegmentScale(CursorLocation));
	InstanceTransform.SetRotation(GetSegmentRotation(CursorLocation).Quaternion());
	InstancedStaticMeshComponent->AddInstance(InstanceTransform);

	//// Create a spline mesh
	//USplineMeshComponent* Spline = CreateSplineMesh();
	//// Update end points
	//FVector StartPosition = GetActorTransform().InverseTransformPosition(CursorLocation);
	//FVector EndPosition = GetActorTransform().InverseTransformPosition(PreviousCursorLocation);
	//Spline->SetStartAndEnd(StartPosition, FVector::ZeroVector, EndPosition, FVector::ZeroVector);

	PreviousCursorLocation = CursorLocation;
}

USplineMeshComponent* AStroke::CreateSplineMesh()
{
	USplineMeshComponent* NewSpline = NewObject<USplineMeshComponent>(this);
	NewSpline->SetMobility(EComponentMobility::Movable);
	NewSpline->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewSpline->SetStaticMesh(SplineMesh);
	NewSpline->SetMaterial(0, SplineMaterial);
	NewSpline->RegisterComponent();

	return NewSpline;
}

FVector AStroke::GetSegmentScale(FVector CursorLocation)
{
	FVector DirectionVector = CursorLocation - PreviousCursorLocation;
	return FVector(DefaultScale.X, DefaultScale.Y, DirectionVector.Size() / 100.0f);
}

FRotator AStroke::GetSegmentRotation(FVector CursorLocation)
{
	FVector DirectionVector = CursorLocation - PreviousCursorLocation;
	DirectionVector.Normalize();

	FVector FlattendDirection = FVector::VectorPlaneProject(DirectionVector, FVector::UpVector);
	FlattendDirection.Normalize();
	float yaw = -acos(FVector::DotProduct(FVector::ForwardVector, FlattendDirection)) * 180.0 / PI;
	if (FVector::DotProduct(FVector::CrossProduct(FVector::ForwardVector, FlattendDirection), FVector::UpVector) > 0)
	{
		yaw *= -1;
	}

	float pitch = -acos(FVector::DotProduct(FVector::UpVector, DirectionVector)) * 180.0 / PI;
	if (FVector::DotProduct(FVector::CrossProduct(FVector::UpVector, DirectionVector), (abs(yaw) > 90 ? -1 : 1) * FVector::RightVector) < 0)
	{
		pitch *= -1;
	}
	float roll = 0.0f;

	return FRotator(pitch, yaw, roll);
}

FVector AStroke::GetSegmentPosition(FVector CursorLocation)
{
	FVector LastLocalPosition = GetActorTransform().InverseTransformPosition((PreviousCursorLocation + CursorLocation) / 2.0);
	return LastLocalPosition;
}