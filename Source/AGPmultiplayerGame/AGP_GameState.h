// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AGP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API AAGP_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AAGP_GameState();
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Category = Timer)
		float gameTime;
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
