// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "RadialSweep.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API ARadialSweep : public ATrapBase
{
	GENERATED_BODY()
public:
	ARadialSweep();
	virtual void BeginPlay() override;
	virtual void UseTrap() override; //MUST define virtual func!
	void Tick(float DeltaTime);

		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* trapSound;

	FVector endLoc;

	bool isMoving;
	float damage;
	UPROPERTY(EditAnywhere)
		float moveAmount;
};
