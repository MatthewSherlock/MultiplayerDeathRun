// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PickupSpawner.h"
#include "PickupBase.h"
#include "GoalArea.h"
#include "AGPmultiplayerGameGameMode.generated.h"

UCLASS(minimalapi)
class AAGPmultiplayerGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAGPmultiplayerGameGameMode();

	virtual void PostLogin(APlayerController* newPC) override;

	int maxNumOfPlayers;

	void SpawnPickups(APickupSpawner* pspawn);

	int RandomNumInArray();

	UPROPERTY(EditAnywhere)
		APickupSpawner* spawner;

	UPROPERTY(EditDefaultsOnly, Category = Goal)
		TSubclassOf<class AGoalArea> goalAreaClass;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class APickupBase>> pickupArray;

	UFUNCTION() //UFUNCTION needed for timer!!!
		void stopGame();

	void gameOver(bool hasWon, int winID);
	void gameOverFromLivesLost(bool hasLost, int lossID);


	void chkForWin(AGoalArea* goal, int winID);
	void chkForDeathLoss(bool hasLost, int lossID);

	FTimerHandle gameTimer;
	UPROPERTY(EditAnywhere)
		float gameDuration;

};



