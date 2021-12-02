// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialSweep.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"



ARadialSweep::ARadialSweep()
{
	instantKill = false;
	isMoving = false;
	damage = 100;
	moveAmount = 0.0f;
}


void ARadialSweep::BeginPlay()
{
	Super::BeginPlay();
	staticMesh->OnComponentHit.AddDynamic(this, &ARadialSweep::OnHit);
	endLoc = FVector(GetActorLocation().X - moveAmount, GetActorLocation().Y, GetActorLocation().Z);

}


void ARadialSweep::UseTrap()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "pushwall used");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, this->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());

	isMoving = true;
	//FVector startLoc = GetActorLocation();
	//FVector endLoc = FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z);
	//FMath::VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f);
	//SetActorLocation(FVector(GetActorLocation().X, VInterpConstantTo(GetActorLocation(), FVector(GetActorLocation().X, (GetActorLocation().Y + 200), GetActorLocation().Z), 1.0f, 1.0f));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, GetActorLocation().ToString());

}

void ARadialSweep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator newRotation = FRotator(0.0f, moveAmount, 0.0f);
	AddActorLocalRotation(newRotation);

}

void ARadialSweep::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());

	if (chr)
	{
	}
}

