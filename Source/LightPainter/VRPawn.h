// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

class UCameraComponent;
class AHandControllerBase;

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

// ----------Base Functions----------
public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// ----------Variables----------
public:
protected:
private:
	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandController;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// References
	UPROPERTY()
	AHandControllerBase* RightHandControllerBase;

	UPROPERTY()
	AHandControllerBase* LeftHandControllerBase;

	// State
	int32 LastInput = 0;

// ----------Custom Functions----------
public:
protected:
private:
	void RightTriggerDown();
	void RightTriggerUp();
	void PaginateRightAxisInput(float Value);
	void UpdateCurrentPage(float Offset);

	void Clear();
};
