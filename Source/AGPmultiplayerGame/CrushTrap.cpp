// Fill out your copyright notice in the Description page of Project Settings.


#include "CrushTrap.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"



ACrushTrap::ACrushTrap()
{
	instantKill = false;
	isMoving = false;
	damage = 100;
	moveAmount = 0.0f;
}


void ACrushTrap::BeginPlay()
{
	Super::BeginPlay();
	endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y), GetActorLocation().Z - moveAmount);

}


void ACrushTrap::UseTrap()
{
	isMoving = true;
}

void ACrushTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), endLoc, DeltaTime, movementSpeed));
	}
	if (GetActorLocation() == endLoc)
		isMoving = false;
}

void ACrushTrap::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());


	if (chr)
	{
		if (instantKill)
		{
			chr->RespawnPlayer();
		}
	}
}
