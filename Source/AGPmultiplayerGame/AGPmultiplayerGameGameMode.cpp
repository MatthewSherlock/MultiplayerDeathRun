// Copyright Epic Games, Inc. All Rights Reserved.

#include "AGPmultiplayerGameGameMode.h"
#include "AGPmultiplayerGameHUD.h"
#include "AGPmultiplayerGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h" //for ActorIterator
#include "AGP_GameState.h" //for gameTime
#include "GameFramework/PlayerState.h"
#include "DrawDebugHelpers.h"


AAGPmultiplayerGameGameMode::AAGPmultiplayerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAGPmultiplayerGameHUD::StaticClass();

	maxNumOfPlayers = 2;
}

void AAGPmultiplayerGameGameMode::PostLogin(APlayerController* newPC) {
	 Super::PostLogin(newPC);
	 GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Post Login");

	AAGP_GameState* gs = GetGameState<AAGP_GameState>();
	if (gs && gs->PlayerArray.Num() == maxNumOfPlayers) {
		UE_LOG(LogTemp, Warning, TEXT("PostLogin Num players: %d"), gs->PlayerArray.Num());
		for (TActorIterator<APickupSpawner> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			spawner = *ActorItr;
			SpawnPickups(spawner);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, spawner->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Post Login");
			GetWorldTimerManager().SetTimer(gameTimer, this, &AAGPmultiplayerGameGameMode::stopGame, gameDuration, false);
		}
	}
	
}

void AAGPmultiplayerGameGameMode::SpawnPickups(APickupSpawner* pspawn)
{
		if (pspawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "spawn pickups");

			pspawn->SpawnPickup(pickupArray[RandomNumInArray()]);
		}
	
}

int AAGPmultiplayerGameGameMode::RandomNumInArray()
{
	int randArrayNum = FMath::RandRange(0, pickupArray.Num() - 1);
	return randArrayNum;
}

void AAGPmultiplayerGameGameMode::stopGame()
{
	gameOver(false, -1);
}

void AAGPmultiplayerGameGameMode::gameOver(bool hasWon, int winID)
{
	AAGP_GameState* gs = GetGameState<AAGP_GameState>();  //get server character
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(gs->PlayerArray[0]->GetPawn());
	chr->MC_GameOver(hasWon, winID);
}

void AAGPmultiplayerGameGameMode::gameOverFromLivesLost(bool hasLost, int lossID)
{
	AAGP_GameState* gs = GetGameState<AAGP_GameState>();  //get server character
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(gs->PlayerArray[0]->GetPawn());
	chr->MC_GameOverNoLives(hasLost, lossID);
}

void AAGPmultiplayerGameGameMode::chkForWin(AGoalArea* goal, int winID)
{
	gameOver(true, winID);
}
void AAGPmultiplayerGameGameMode::chkForDeathLoss(bool hasLost, int lossID)
{
	gameOverFromLivesLost(hasLost, lossID);
}