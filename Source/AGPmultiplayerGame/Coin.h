
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API ACoin : public APickupBase
{
	GENERATED_BODY()
public:
	ACoin();
	virtual void BeginPlay() override;


	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
		float pickupScore;


};
