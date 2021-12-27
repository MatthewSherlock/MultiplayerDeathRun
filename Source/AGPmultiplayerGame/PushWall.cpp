// Fill out your copyright notice in the Description page of Project Settings.


#include "PushWall.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


APushWall::APushWall()
{
	instantKill = false;
	isMoving = false;
}


void APushWall::BeginPlay()
{
	Super::BeginPlay();
	endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y + 1000), GetActorLocation().Z);

}


void APushWall::UseTrap()
{


	FVector currPos = GetActorLocation();

	isMoving = true;

	if (GetLocalRole() == ROLE_Authority) {
		MC_UseTrap(currPos);  //update trap pos 
	}
	else
		ServerUseTrap(currPos);
		
}

void APushWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), endLoc, DeltaTime, movementSpeed));
	}
	if (GetActorLocation() == endLoc)
		isMoving = false;
}

void APushWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);

	if (chr)
	{
		if (instantKill)
		{
			chr->RespawnPlayer();
		}
	}
}

void APushWall::MC_UpdateTrapPos_Implementation(const FVector& newLoc)
{
	SetActorLocation(newLoc); //replic movement must be on!
}


void APushWall::MC_UseTrap_Implementation(const FVector& newLoc)
{
	MC_UpdateTrapPos(newLoc);
}



void APushWall::ServerUseTrap_Implementation(const FVector& newLoc)
{
	MC_UpdateTrapPos(newLoc);
}

