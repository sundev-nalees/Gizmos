// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GizmoSelectableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGizmoSelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GIZMOS_API IGizmoSelectableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool IsGizmoEnabled() const = 0;

};
