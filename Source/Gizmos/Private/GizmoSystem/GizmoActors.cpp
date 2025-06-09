// Fill out your copyright notice in the Description page of Project Settings.


#include "GizmoSystem/GizmoActors.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AGizmoActors::AGizmoActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	AxisX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxisX"));
	AxisY = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxisY"));
	AxisZ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxisZ"));

	AxisX->SetupAttachment(RootComponent);
	AxisY->SetupAttachment(RootComponent);
	AxisZ->SetupAttachment(RootComponent);

	ActiveAxis = EGizmoAxis::None;
	TargetActor = nullptr;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Warning: Gizmo axis not set!"));
}

// Called when the game starts or when spawned
void AGizmoActors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGizmoActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(TargetActor)
	{
		SetActorLocation(TargetActor->GetActorLocation());
	}

}

void AGizmoActors::AttachToTarget(AActor* Target)
{
	TargetActor = Target;
	SetActorHiddenInGame(false);
}

void AGizmoActors::SetActiveAxis(EGizmoAxis NewAxis)
{
	ActiveAxis = NewAxis;
}

void AGizmoActors::ClearAxis()
{
	ActiveAxis = EGizmoAxis::None;
}

void AGizmoActors::SetupAxis(UStaticMeshComponent* Axis, FVector Direction, FLinearColor Color)
{
	
	static  ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Engine/BasicShapes/Cylinder"));

	if(Mesh.Succeeded())
	{
		Axis->SetStaticMesh(Mesh.Object);
		Axis->SetWorldScale3D(FVector(0.1f, 0.1f, 2.0f));
		Axis->SetRelativeRotation(Direction.Rotation());
		Axis->SetCollisionProfileName(TEXT("BlockAll"));
		Axis->SetMobility(EComponentMobility::Movable);
		UMaterialInstanceDynamic* Mat = Axis->CreateAndSetMaterialInstanceDynamic(0);
		if (Mat)Mat->SetVectorParameterValue("BaseColor", Color);
		
	
	}

}

