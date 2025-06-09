// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/GizmoPlayerController.h"

AGizmoPlayerController::AGizmoPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bDragging = false;
	bShowMouseCursor = true;
}

void AGizmoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(!GizmoManager)
	{
		GizmoManager = GetWorld()->SpawnActor<AGizmosManager>(AGizmosManager::StaticClass());
		if (!GizmoManager)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Warning: Gizmo shaaaa!"));
		}
		
	}
}

void AGizmoPlayerController::Tick(float DeltaSeconds)
{

	if (bDragging && GizmoManager)
	{
		FVector Origin, Direction;
		GetMouseWorldDirection(Origin, Direction);
		FVector TracePoint = Origin + Direction * 1000.f;
		GizmoManager->HandleMouseMove(TracePoint);
	}
}

void AGizmoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AGizmoPlayerController::OnLeftMousePressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AGizmoPlayerController::OnLeftMouseReleased);
	//InputComponent->BindAxis("Turn", this, &AGizmoPlayerController::OnMouseMoved);
}

void AGizmoPlayerController::OnLeftMousePressed()
{
	FVector Orgin, Direction;
	GetMouseWorldDirection(Orgin, Direction);

	if(GizmoManager)
	{
		GizmoManager->HandelClick(Orgin, Direction);
		bDragging = true;
		
	}
	
	CachedWorldOrgine = Orgin;
	CachedWorldDirection = Direction;
}

void AGizmoPlayerController::OnLeftMouseReleased()
{
	if(GizmoManager)
	{
		GizmoManager->HandleRelease();

	}

	bDragging = false;
}

void AGizmoPlayerController::OnMouseMoved()
{
	if (bDragging && GizmoManager)
	{
		FVector Origin, Direction;
		GetMouseWorldDirection(Origin, Direction);
		FVector TracePoint = Origin + Direction * 1000.f;
		GizmoManager->HandleMouseMove(TracePoint);
	}
}

FVector AGizmoPlayerController::GetMouseWorldDirection(FVector& OutOrigin, FVector& OutDirection) const
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	DeprojectScreenPositionToWorld(MouseX, MouseY, OutOrigin, OutDirection);
	return OutOrigin + OutDirection * 10000.0f;
}
