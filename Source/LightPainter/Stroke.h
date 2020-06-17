// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

class USplineMeshComponent;
class UInstancedStaticMeshComponent;

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

	// Config
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* SplineMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* SplineMaterial;

	// State
	FVector PreviousCursorLocation;

	UPROPERTY(EditAnywhere)
	FVector DefaultScale;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	// ----------Custom Functions----------
public:
	void Update(FVector CursorLocation);
protected:
private:
	USplineMeshComponent * CreateSplineMesh();

	FVector GetSegmentScale(FVector CursorLocation);
	FRotator GetSegmentRotation(FVector CursorLocation);
	FVector GetSegmentPosition(FVector CursorLocation);

};
