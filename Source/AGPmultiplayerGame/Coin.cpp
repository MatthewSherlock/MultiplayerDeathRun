// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg

ACoin::ACoin()
{
	pickupScore = 100.0f;
}


void ACoin::BeginPlay()
{
	Super::BeginPlay();
	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);
}
void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	if (chr)
	{
		chr->currScore = chr->currScore + pickupScore;
		if (coinSound)
			UGameplayStatics::PlaySoundAtLocation(this, coinSound, GetActorLocation());

		Destroy();
	}
}
