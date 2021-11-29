// Fill out your copyright notice in the Description page of Project Settings.


#include "AGP_GameState.h"
#include "Net/UnrealNetwork.h" //for replication

AAGP_GameState::AAGP_GameState()
{
	gameTime = 0.0f;
}

void AAGP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Update replicated properties
	DOREPLIFETIME(AAGP_GameState, gameTime);
}
