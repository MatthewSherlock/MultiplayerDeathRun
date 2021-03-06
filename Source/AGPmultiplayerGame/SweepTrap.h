// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "SweepTrap.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API ASweepTrap : public ATrapBase
{
	GENERATED_BODY()
public:
	ASweepTrap();
	virtual void BeginPlay() override;
	virtual void UseTrap() override; //MUST define virtual func!
	void Tick(float DeltaTime);

		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* trapSound;

	FVector endLoc;

	bool isMoving;
	float damage;

};
