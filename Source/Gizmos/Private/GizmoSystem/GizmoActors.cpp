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
	HandleXY = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleXY"));
	HandleYZ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleYZ"));
	HandleXZ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleXZ"));

	HandleXY->ComponentTags.Add("GizmoPlaneXY");
	HandleYZ->ComponentTags.Add("GizmoPlaneYZ");
	HandleXZ->ComponentTags.Add("GizmoPlaneXY");

	/*AxisX->SetupAttachment(RootComponent);
	AxisY->SetupAttachment(RootComponent);
	AxisZ->SetupAttachment(RootComponent);*/

	

	HitBoxX = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxX"));
	HitBoxX->SetupAttachment(AxisX);
	/*HitBoxX->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	HitBoxX->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxX->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxX->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxX->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block)*/;
	HitBoxX->ComponentTags.Add(FName("GizmoAxisX"));



	HitBoxY = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxY"));
	HitBoxY->SetupAttachment(AxisY);
	/*HitBoxY->SetBoxExtent(FVector(60.f, 10.f, 10.f));
	HitBoxY->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxY->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxY->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxY->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);*/
	HitBoxY->ComponentTags.Add(FName("GizmoAxisY"));

	

	

	HitBoxZ = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxZ"));
	HitBoxZ->SetupAttachment(AxisZ);
	/*HitBoxZ->SetBoxExtent(FVector(70.f, 10.f, 10.f));
	HitBoxZ->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	HitBoxZ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitBoxZ->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBoxZ->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);*/
	HitBoxZ->ComponentTags.Add(FName("GizmoAxisZ"));


	SetupAxis(AxisX, FVector(70, 0, 0), FLinearColor::Red);
	SetupAxis(AxisY, FVector(0, 70, 0), FLinearColor::Green);
	SetupAxis(AxisZ, FVector(0, 0, 70), FLinearColor::Blue);

	SetupHitBox(HitBoxX);
	SetupHitBox(HitBoxY);
	SetupHitBox(HitBoxZ);

	SetupPlainAxis(HandleXY, FVector(13, 19, 0), FRotator(0, 0, 0), FVector(0.4f));
	SetupPlainAxis(HandleYZ, FVector(20, 1, 23), FRotator(-90, 90, 0), FVector(0.4f));
	SetupPlainAxis(HandleXZ, FVector(0, 24, 22), FRotator(-90, 0, 0), FVector(0.4f));

	SetupFreeAxis();

	ActiveAxis = EGizmoAxis::None;
	TargetActor = nullptr;
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
	Axis->SetupAttachment(RootComponent);
	Axis->ArrowColor = FColor(Color.ToFColor(true));
	Axis->ArrowSize = 2.0f; 
	Axis->bIsScreenSizeScaled = true;
	Axis->SetRelativeRotation(Direction.Rotation());

	Axis->SetHiddenInGame(false);
	
}

void AGizmoActors::SetupHitBox(UBoxComponent* Axis)
{
	
	Axis->SetBoxExtent(FVector(70.f, 10.f, 10.f));
	Axis->SetRelativeLocation(FVector(60.f, 0.f, 0.f));
	Axis->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Axis->SetCollisionResponseToAllChannels(ECR_Ignore);
	Axis->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AGizmoActors::SetupFreeAxis()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMesh.Succeeded())
	{
		HandleFree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleFree"));
		HandleFree->SetupAttachment(RootComponent);
		HandleFree->SetStaticMesh(SphereMesh.Object);
		HandleFree->SetRelativeLocation(FVector(0, 0, 0));
		HandleFree->SetRelativeScale3D(FVector(0.3f));
		HandleFree->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		HandleFree->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		HandleFree->ComponentTags.Add("GizmoFreeMove");
	}
}

void AGizmoActors::SetupPlainAxis(UStaticMeshComponent* HandlePlain, const FVector& Direction, const FRotator& Rotation, const FVector& WorldScale)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane"));
	

	if (PlaneMesh.Succeeded())
	{
		
		HandlePlain->SetupAttachment(RootComponent);
		HandlePlain->SetStaticMesh(PlaneMesh.Object);
		HandlePlain->SetRelativeLocation(Direction);
		HandlePlain->SetRelativeRotation(Rotation);
		HandlePlain->SetWorldScale3D(WorldScale);
		HandlePlain->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		HandlePlain->SetCollisionResponseToAllChannels(ECR_Ignore);
		HandlePlain->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

	

}

