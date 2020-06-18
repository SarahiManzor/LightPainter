// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

class USplineMeshComponent;
class UInstancedStaticMeshComponent;
class UWorld;
struct FStrokeState;

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();
protected:
	virtual void BeginPlay() override;

	// ----------Variables----------
public:
protected:
private:
	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* CylinderInstancedStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* SphereInstancedStaticMeshComponent;

	// State
	FVector PreviousCursorLocation;
	TArray<FVector> ControlPoints;

	UPROPERTY(EditAnywhere)
	FVector DefaultScale;

	// ----------Custom Functions----------
public:
	void Update(FVector CursorLocation);
	FStrokeState SerializeToStruct() const;
	static AStroke* SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState &StrokeState);

protected:
private:
	FVector GetSegmentScale(FVector CursorLocation) const;
	FRotator GetSegmentRotation(FVector CursorLocation) const;
	FQuat GetSegmentRotationQ(FVector CursorLocation) const;
	FVector GetSegmentPosition(FVector CursorLocation) const;

	FTransform GetNextSegmentTransform(FVector CursorLocation) const;
	FTransform GetNextJointTransform(FVector CursorLocation) const;

};
