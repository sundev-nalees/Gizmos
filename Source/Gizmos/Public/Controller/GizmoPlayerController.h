// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GizmoSystem/GizmosManager.h"
#include "GizmoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GIZMOS_API AGizmoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGizmoPlayerController();

protected:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupInputComponent()override;

private:

	UPROPERTY()
	AGizmosManager* GizmoManager;

	bool bDragging;
	FVector CachedWorldDirection;
	FVector CachedWorldOrgine;

	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void OnMouseMoved();

	FVector GetMouseWorldDirection(FVector& OutOrigin, FVector& OutDirection)const;

	
};
