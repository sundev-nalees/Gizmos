// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GizmoActors.generated.h"

UENUM()

enum class EGizmoAxis:uint8
{
	None,X,Y,Z
};


UCLASS(Blueprintable)
class GIZMOS_API AGizmoActors : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGizmoActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachToTarget(AActor* Target);

	void SetActiveAxis(EGizmoAxis NewAxis);

	void ClearAxis();

	EGizmoAxis GetActiveAxis()const { return ActiveAxis; }

	AActor* GetTarget()const { return TargetActor; }


protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AxisX;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AxisY;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AxisZ;

	UPROPERTY()
	AActor* TargetActor;

	EGizmoAxis ActiveAxis;

	void SetupAxis(UStaticMeshComponent* Axis, FVector Direction, FLinearColor Color);
};
