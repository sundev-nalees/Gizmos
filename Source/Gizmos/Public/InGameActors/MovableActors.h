// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"GizmoSystem/GizmoSelectableInterface.h"
#include "MovableActors.generated.h"

UCLASS()
class GIZMOS_API AMovableActors : public AActor, public IGizmoSelectableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovableActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsGizmoEnabled()const override { return bGizmoEnable; }

	virtual void SetCollision(bool bEnabled) override;

private:

	bool bGizmoEnable = true;

};
