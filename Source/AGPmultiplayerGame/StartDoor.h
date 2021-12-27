// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "StartDoor.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API AStartDoor : public ATrapBase
{
	GENERATED_BODY()
public:
	virtual void UseTrap() override; //MUST define virtual func!

};
