// Copyright Epic Games, Inc. All Rights Reserved.

#include "AGPmultiplayerGameGameMode.h"
#include "AGPmultiplayerGameHUD.h"
#include "AGPmultiplayerGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "AGP_GameState.h" //for gameTime

AAGPmultiplayerGameGameMode::AAGPmultiplayerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAGPmultiplayerGameHUD::StaticClass();
}

void AAGPmultiplayerGameGameMode::PostLogin(APlayerController* newPC) {
	Super::PostLogin(newPC);

	AAGP_GameState* gs = GetGameState<AAGP_GameState>();
	if (gs && gs->PlayerArray.Num() == maxNumOfPlayers) {
		UE_LOG(LogTemp, Warning, TEXT("PostLogin Num players: %d"), gs->PlayerArray.Num());
		SpawnPickups(spawner);
	}
}

void AAGPmultiplayerGameGameMode::SpawnPickups(APickupSpawner* pspawn)
{
	if (pspawn)
	{
		pspawn->SpawnPickup(pickupArray[0]);
	}
}
