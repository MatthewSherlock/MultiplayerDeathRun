// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PickupSpawner.h"
#include "PickupBase.h"
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

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickupSpawner*> spawner;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class APickupBase>> pickupArray;
};



