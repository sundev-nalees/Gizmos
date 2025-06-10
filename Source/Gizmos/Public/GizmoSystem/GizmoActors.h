// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
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

	UArrowComponent* GetAxisX() const { return AxisX; }
	UArrowComponent* GetAxisY() const { return AxisY; }
	UArrowComponent* GetAxisZ() const { return AxisZ; }

protected:

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* AxisX;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* AxisY;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* AxisZ;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HitBoxX;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HitBoxY;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HitBoxZ;

	UPROPERTY()
	AActor* TargetActor;

	EGizmoAxis ActiveAxis;

	void SetupAxis(UArrowComponent* Axis, const FVector& Direction, const FLinearColor& Color);
};
