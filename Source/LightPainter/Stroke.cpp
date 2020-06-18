// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h" 
#include "Saving/PainterSaveGame.h"
#include "Engine/World.h"

// Sets default values
AStroke::AStroke()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CylinderInstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CylinderInstancedStaticMeshComponent"));
	CylinderInstancedStaticMeshComponent->SetupAttachment(Root);

	SphereInstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SphereInstancedStaticMeshComponent"));
	SphereInstancedStaticMeshComponent->SetupAttachment(Root);

	DefaultScale = FVector::OneVector;
}

void AStroke::BeginPlay()
{
	PreviousCursorLocation = GetActorLocation();

	if (!CylinderInstancedStaticMeshComponent->GetStaticMesh())
	{
		CylinderInstancedStaticMeshComponent->SetStaticMesh(SplineMesh);
	}
	CylinderInstancedStaticMeshComponent->SetMaterial(0, SplineMaterial);
	if (!SphereInstancedStaticMeshComponent->GetStaticMesh())
	{
		SphereInstancedStaticMeshComponent->SetStaticMesh(JointMesh);
	}
	SphereInstancedStaticMeshComponent->SetMaterial(0, SplineMaterial);

	SphereInstancedStaticMeshComponent->AddInstance(GetNextJointTransform(PreviousCursorLocation));
}

FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState StrokeState;
	StrokeState.Class = GetClass();
	StrokeState.ControlPoints = ControlPoints;
	StrokeState.Location = GetActorLocation();

	return StrokeState;
}

AStroke* AStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState &StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.Class, StrokeState.Location, FRotator::ZeroRotator);
	for (FVector ControlPoint : StrokeState.ControlPoints)
	{
		Stroke->Update(ControlPoint);
	}

	return Stroke;
}

void AStroke::Update(FVector CursorLocation)
{
	FVector DirectionVector = CursorLocation - PreviousCursorLocation;
	if (DirectionVector.Size() < 0.4) return;

	ControlPoints.Add(CursorLocation);
	CylinderInstancedStaticMeshComponent->AddInstance(GetNextSegmentTransform(CursorLocation));

	SphereInstancedStaticMeshComponent->AddInstance(GetNextJointTransform(CursorLocation));

	//// Create a spline mesh
	//USplineMeshComponent* Spline = CreateSplineMesh();
	//// Update end points
	//FVector StartPosition = GetActorTransform().InverseTransformPosition(CursorLocation);
	//FVector EndPosition = GetActorTransform().InverseTransformPosition(PreviousCursorLocation);
	//Spline->SetStartAndEnd(StartPosition, FVector::ZeroVector, EndPosition, FVector::ZeroVector);

	PreviousCursorLocation = CursorLocation;
}

FTransform AStroke::GetNextSegmentTransform(FVector CursorLocation)
{
	FTransform CylinderInstanceTransform;
	CylinderInstanceTransform.SetLocation(GetSegmentPosition(CursorLocation));
	CylinderInstanceTransform.SetScale3D(GetSegmentScale(CursorLocation));
	CylinderInstanceTransform.SetRotation(GetSegmentRotation(CursorLocation).Quaternion());
	return CylinderInstanceTransform;
}

FTransform AStroke::GetNextJointTransform(FVector CursorLocation)
{
	FTransform SphereInstanceTransform;
	SphereInstanceTransform.SetLocation(GetActorTransform().InverseTransformPosition(CursorLocation));
	SphereInstanceTransform.SetScale3D(DefaultScale);
	SphereInstanceTransform.SetRotation(GetSegmentRotation(CursorLocation).Quaternion());
	return SphereInstanceTransform;
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

FQuat AStroke::GetSegmentRotationQ(FVector CursorLocation)
{
	FVector DirectionVector = CursorLocation - PreviousCursorLocation;
	DirectionVector.Normalize();
	return FQuat::FindBetweenNormals(FVector::UpVector, DirectionVector);
}

FVector AStroke::GetSegmentPosition(FVector CursorLocation)
{
	FVector LastLocalPosition = GetActorTransform().InverseTransformPosition((PreviousCursorLocation + CursorLocation) / 2.0);
	return LastLocalPosition;
}