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

	AxisX = CreateDefaultSubobject<UArrowComponent>(TEXT("AxisX"));
	AxisY = CreateDefaultSubobject<UArrowComponent>(TEXT("AxisY"));
	AxisZ = CreateDefaultSubobject<UArrowComponent>(TEXT("AxisZ"));

	AxisX->SetupAttachment(RootComponent);
	AxisY->SetupAttachment(RootComponent);
	AxisZ->SetupAttachment(RootComponent);

	AxisX->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AxisX->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AxisX->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	HitBoxX = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxX"));
	HitBoxX->SetupAttachment(AxisX);
	HitBoxX->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	HitBoxX->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxX->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxX->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxX->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	HitBoxX->ComponentTags.Add(FName("GizmoAxisX"));


	AxisY->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AxisY->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AxisY->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	HitBoxY = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxY"));
	HitBoxY->SetupAttachment(AxisY);
	HitBoxY->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	HitBoxY->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxY->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxY->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxY->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	HitBoxY->ComponentTags.Add(FName("GizmoAxisY"));

	

	AxisZ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AxisZ->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AxisZ->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	HitBoxZ = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxZ"));
	HitBoxZ->SetupAttachment(AxisZ);
	HitBoxZ->SetBoxExtent(FVector(70.f, 10.f, 10.f));
	HitBoxZ->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxZ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxZ->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxZ->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	HitBoxZ->ComponentTags.Add(FName("GizmoAxisZ"));

	

	ActiveAxis = EGizmoAxis::None;
	TargetActor = nullptr;

	SetupAxis(AxisX, FVector(1, 0, 0), FLinearColor::Red);
	SetupAxis(AxisY, FVector(0, 1, 0), FLinearColor::Green);
	SetupAxis(AxisZ, FVector(0, 0, 1), FLinearColor::Blue);
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

void AGizmoActors::SetAxisHighlight(EGizmoAxis Axis)
{
	if (AxisX) AxisX->ArrowColor = FColor::Red;
	if (AxisY) AxisY->ArrowColor = FColor::Green;
	if (AxisZ) AxisZ->ArrowColor = FColor::Blue;

	// Highlight selected
	switch (Axis)
	{
	case EGizmoAxis::X:
		AxisX->ArrowColor = FColor::Yellow;
		break;
	case EGizmoAxis::Y:
		AxisY->ArrowColor = FColor::Yellow;
		break;
	case EGizmoAxis::Z:
		AxisZ->ArrowColor = FColor::Yellow;
		break;
	default:
		break;
	}

	// Force update of arrow visuals
	AxisX->MarkRenderStateDirty();
	AxisY->MarkRenderStateDirty();
	AxisZ->MarkRenderStateDirty();
}

void AGizmoActors::SetupAxis(UArrowComponent* Axis, const FVector& Direction, const FLinearColor& Color)	
{
	if (!Axis) return;

	Axis->ArrowColor = FColor(Color.ToFColor(true));
	Axis->ArrowSize = 2.0f; // Make it large enough to be visible
	Axis->bIsScreenSizeScaled = true; // Optional: scales with screen size
	Axis->SetRelativeRotation(Direction.Rotation());
	Axis->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Axis->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Axis->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	Axis->SetHiddenInGame(false);
	
}

