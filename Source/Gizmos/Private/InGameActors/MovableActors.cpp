// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameActors/MovableActors.h"

// Sets default values
AMovableActors::AMovableActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovableActors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovableActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovableActors::SetCollision(bool bEnabled)
{
	TInlineComponentArray<UPrimitiveComponent*> PrimitiveComponents(this);

	for (UPrimitiveComponent* Prim : PrimitiveComponents)
	{
		// Change only the visibility channel
		Prim->SetCollisionResponseToChannel(
			ECC_Visibility,
			bEnabled ? ECR_Block : ECR_Ignore
		);
	}
}

