// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrapsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTrapsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AGPMULTIPLAYERGAME_API ITrapsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void UseTrap();
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
