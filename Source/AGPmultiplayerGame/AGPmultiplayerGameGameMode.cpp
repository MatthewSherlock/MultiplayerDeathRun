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
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAGPmultiplayerGameHUD::StaticClass();

	maxNumOfPlayers = 2;
}

void AAGPmultiplayerGameGameMode::PostLogin(APlayerController* newPC) {
	 Super::PostLogin(newPC);

	AAGP_GameState* gs = GetGameState<AAGP_GameState>();
	if (gs && gs->PlayerArray.Num() == maxNumOfPlayers) {
		for (TActorIterator<APickupSpawner> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			spawner = *ActorItr;
			SpawnPickups(spawner);
			GetWorldTimerManager().SetTimer(secondsTimer, this, &AAGPmultiplayerGameGameMode::UpdateTimer, 1.0f, true);
		}
	}
	
}

void AAGPmultiplayerGameGameMode::SpawnPickups(APickupSpawner* pspawn)
{
		if (pspawn)
		{
			pspawn->SpawnPickup(pspawn->pickupArray[RandomNumInArray(pspawn)]);
		}
	
}

int AAGPmultiplayerGameGameMode::RandomNumInArray(APickupSpawner* pspawn)
{
	int randArrayNum = FMath::RandRange(0, pspawn->pickupArray.Num() - 1);
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
	CalculateFinalScore();
	GetWorldTimerManager().PauseTimer(secondsTimer);
	chr->MC_GameOver(hasWon, winID);
}

void AAGPmultiplayerGameGameMode::gameOverFromLivesLost(bool hasLost, int lossID)
{
	AAGP_GameState* gs = GetGameState<AAGP_GameState>();  //get server character
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(gs->PlayerArray[0]->GetPawn());
	GetWorldTimerManager().PauseTimer(secondsTimer);
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

void AAGPmultiplayerGameGameMode::UpdateTimer()
{
	AAGP_GameState* gs = GetGameState<AAGP_GameState>();
	gs->gameTime += 1.0f;	//incr time
}

void AAGPmultiplayerGameGameMode::CalculateFinalScore()
{
	AAGP_GameState* gs = GetGameState<AAGP_GameState>();
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(gs->PlayerArray[0]->GetPawn());

	totalScore = (chr->currScore + (100 - gs->gameTime));
}
