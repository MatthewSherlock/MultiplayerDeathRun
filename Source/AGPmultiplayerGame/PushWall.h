// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "PushWall.generated.h"

/**
 * 
 */
UCLASS()
class AGPMULTIPLAYERGAME_API APushWall : public ATrapBase
{
	GENERATED_BODY()
public:
	APushWall();
	virtual void BeginPlay() override;
	virtual void UseTrap() override; //MUST define virtual func!
	void Tick(float DeltaTime);

		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UFUNCTION(NetMulticast, Reliable)
		void MC_UpdateTrapPos(const FVector& newLoc);
	void MC_UpdateTrapPos_Implementation(const FVector& newLoc);
	
	UFUNCTION(NetMulticast, Reliable)
		void MC_UseTrap(const FVector& newLoc);
	void MC_UseTrap_Implementation(const FVector& newLoc);
	UFUNCTION(Server, Reliable)
		void ServerUseTrap(const FVector& newLoc);
	void ServerUseTrap_Implementation(const FVector& newLoc);
	
	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* trapSound;

	FVector endLoc;

	bool isMoving;
};
