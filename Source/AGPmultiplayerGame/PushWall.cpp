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
	staticMesh->OnComponentHit.AddDynamic(this, &APushWall::OnHit);
	endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y + 1000), GetActorLocation().Z);

}


void APushWall::UseTrap()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "pushwall used");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, this->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());

	FVector currPos = GetActorLocation();

	isMoving = true;
	//FVector startLoc = GetActorLocation();
	//FVector endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z);
	//FMath::VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f);
	//SetActorLocation(FVector(GetActorLocation().X, VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());
	/*
	if (GetLocalRole() == ROLE_Authority) {
		MC_UseTrap(currPos);  //update trap pos 
	}
	else
		ServerUseTrap(currPos);
		*/
}

void APushWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "moving");

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), endLoc, DeltaTime, 1000.0f));
	}
	if (GetActorLocation() == endLoc)
		isMoving = false;
}

void APushWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);

	if (chr)
	{
	}
}
/*
void APushWall::MC_UpdateTrapPos_Implementation(const FVector& newLoc)
{
	SetActorLocation(newLoc); //replic movement must be on!
}

void APushWall::MC_UseTrap(const FVector& newLoc)
{
}

void APushWall::MC_UseTrap_Implementation(const FVector& newLoc)
{
	MC_UpdateTrapPos(newLoc);
}

void APushWall::ServerUseTrap(const FVector& newLoc)
{
}

void APushWall::ServerUseTrap_Implementation(const FVector& newLoc)
{
	MC_UseTrap(newLoc);
}
*/
