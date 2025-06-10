// Fill out your copyright notice in the Description page of Project Settings.


#include "GizmoSystem/GizmosManager.h"
#include "GizmoSystem/GizmoSelectableInterface.h"
// Sets default values
AGizmosManager::AGizmosManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gizmo = nullptr;
	SelectedActor = nullptr;

}

// Called when the game starts or when spawned
void AGizmosManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnGizmo();
	
}

// Called every frame
void AGizmosManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGizmosManager::HandelClick(FVector WorldOrigin, FVector WorldDirection)
{
	
	FHitResult Hit;
	FVector End = WorldOrigin + WorldDirection * 10000;
	GetWorld()->LineTraceSingleByChannel(Hit, WorldOrigin, End, ECC_Visibility);
	DrawDebugLine(GetWorld(), WorldOrigin, End, Hit.bBlockingHit? FColor::Green : FColor::Red, false, 2.0f, 0, 1.0f);
	if (!Hit.bBlockingHit || !Hit.GetComponent()) return;

	
	if (Hit.GetComponent()->ComponentHasTag("GizmoAxisX"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: X Axis %s"), *Hit.GetComponent()->GetName());
		Gizmo->SetActiveAxis(EGizmoAxis::X);
		return;
	}
	else if (Hit.GetComponent()->ComponentHasTag("GizmoAxisY"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: Y Axis %s"), *Hit.GetComponent()->GetName());
		Gizmo->SetActiveAxis(EGizmoAxis::Y);
		return;
	}
	else if (Hit.GetComponent()->ComponentHasTag("GizmoAxisZ"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: Z Axis %s"), *Hit.GetComponent()->GetName());
		Gizmo->SetActiveAxis(EGizmoAxis::Z);
		return;
	}


	AActor* HitActor = Hit.GetActor();
	if (HitActor && HitActor->GetClass()->ImplementsInterface(UGizmoSelectableInterface::StaticClass()))
	{
		if (IGizmoSelectableInterface* Interface = Cast<IGizmoSelectableInterface>(HitActor))
		{
			if (Interface->IsGizmoEnabled())
			{
				SelectedActor = HitActor;
				Gizmo->AttachToTarget(SelectedActor);
				UE_LOG(LogTemp, Warning, TEXT("Selected actor: %s"), *HitActor->GetName());
			}
		}
	}
}

void AGizmosManager::HandleMouseMove(FVector WorldLocation)
{
	if(Gizmo&&Gizmo->GetTarget())
	{
		UpdateTargetLocation(WorldLocation);

		
	}
}

void AGizmosManager::HandleRelease()
{
	if(Gizmo)
	{
		Gizmo->ClearAxis();
	}
}

void AGizmosManager::SpawnGizmo()
{
	
	FActorSpawnParameters Params;
	Gizmo = GetWorld()->SpawnActor<AGizmoActors>(AGizmoActors::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);
	Gizmo->SetActorHiddenInGame(true);
	if(!Gizmo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Warning: Gizmo Fucked"));
	}
}

void AGizmosManager::UpdateTargetLocation(const FVector& CurrentWorldPos)
{
	if (!SelectedActor) return;

	FVector Delta = CurrentWorldPos - LastMouseWorld;

	switch (Gizmo->GetActiveAxis())
	{
	case EGizmoAxis::X:
		SelectedActor->AddActorWorldOffset(FVector(Delta.X, 0, 0));
		break;

	case EGizmoAxis::Y:
		SelectedActor->AddActorWorldOffset(FVector(0, Delta.Y, 0));
		break;

	case EGizmoAxis::Z:
		SelectedActor->AddActorWorldOffset(FVector(0, 0, Delta.Z));
		break;

	default:
		break;
	}

	LastMouseWorld = CurrentWorldPos;
}

