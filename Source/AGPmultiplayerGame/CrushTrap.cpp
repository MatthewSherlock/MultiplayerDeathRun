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
	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACrushTrap::OnBeginOverlap);
	endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y), GetActorLocation().Z - moveAmount);

}


void ACrushTrap::UseTrap()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, this->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());

	isMoving = true;
	//FVector startLoc = GetActorLocation();
	//FVector endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z);
	//FMath::VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f);
	//SetActorLocation(FVector(GetActorLocation().X, VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());

}

void ACrushTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{

		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), endLoc, DeltaTime * 0.2f, 1000.0f));
	}
	if (GetActorLocation() == endLoc)
		isMoving = false;
}

void ACrushTrap::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "crush hit");

	if (chr)
	{
		chr->health -= damage;
	}
}

void ACrushTrap::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "crush hit");

	if (chr)
	{
		chr->health -= damage;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Player hit");

	}
}
