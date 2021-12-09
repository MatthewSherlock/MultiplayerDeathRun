// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "SpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API ASpeedPickup : public APickupBase
{
	GENERATED_BODY()
public:
	ASpeedPickup();
	virtual void BeginPlay() override;
	virtual void UsePickup() override; //MUST define virtual func!
	void PickupEnd();
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere)
		float speedAmount;

	float stdWalkSpeed;




};
