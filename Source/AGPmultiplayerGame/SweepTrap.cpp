// Fill out your copyright notice in the Description page of Project Settings.


#include "SweepTrap.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"



ASweepTrap::ASweepTrap()
{
	instantKill = false;
	isMoving = false;
	damage = 100;
	moveAmount = 0.0f;
}


void ASweepTrap::BeginPlay()
{
	Super::BeginPlay();
	endLoc = FVector(GetActorLocation().X - moveAmount, GetActorLocation().Y, GetActorLocation().Z);

}


void ASweepTrap::UseTrap()
{

	isMoving = true;

}

void ASweepTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), endLoc, DeltaTime, movementSpeed));
	}
	if (GetActorLocation() == endLoc)
		isMoving = false;
}

void ASweepTrap::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
