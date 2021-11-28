// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "JumpPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API AJumpPickup : public APickupBase
{
	GENERATED_BODY()
public:
	AJumpPickup();
	virtual void BeginPlay() override;
	virtual void UsePickup() override; //MUST define virtual func!
	UFUNCTION()
	void PickupEnd();
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere)
		float jumpAmount;

	float stdJumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* pickupSound;
};
