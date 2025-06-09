// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GizmoSystem/GizmoActors.h"
#include "GizmosManager.generated.h"

UCLASS()
class GIZMOS_API AGizmosManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGizmosManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandelClick(FVector WorldOrigin, FVector WorldDirection);
	void HandleMouseMove(FVector WorldLocation);
	void HandleRelease();


private:

	AGizmoActors* Gizmo;
	AActor* SelectedActor;
	FVector LastMouseWorld;

	void SpawnGizmo();
	
	void UpdateTargetLocation(const FVector& CurrentWorldPos);
};
