// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "CrushTrap.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API ACrushTrap : public ATrapBase
{
	GENERATED_BODY()
public:
	ACrushTrap();
	virtual void BeginPlay() override;
	virtual void UseTrap() override; //MUST define virtual func!
	void Tick(float DeltaTime);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* trapSound;

	FVector endLoc;

	bool isMoving;
};
