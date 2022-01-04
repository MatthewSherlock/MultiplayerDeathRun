// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "GameFramework/CharacterMovementComponent.h"
ASpeedPickup::ASpeedPickup()
{
	speedAmount = 10000.0f;
}


void ASpeedPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ASpeedPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	if (chr)
	{
		if (!chr->currPickup)
		{
			chr->GrabPickup(this);

			if (pickupSound)
				UGameplayStatics::PlaySoundAtLocation(this, pickupSound, GetActorLocation());

			SetActorHiddenInGame(true);
			staticMesh->DestroyComponent();
		}
	}
}

void ASpeedPickup::UsePickup() 
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr)
	{
		if (!isUsed) {
			stdWalkSpeed = chr->GetCharacterMovement()->MaxWalkSpeed;
			chr->GetCharacterMovement()->MaxWalkSpeed = chr->GetCharacterMovement()->MaxWalkSpeed + speedAmount;
			GetWorldTimerManager().SetTimer(endEffect, this, &ASpeedPickup::PickupEnd, effectTime, false);
			isUsed = true;
		}
	}
}

void ASpeedPickup::PickupEnd()
{

	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr)
	{
		chr->currPickup = nullptr;
		chr->GetCharacterMovement()->MaxWalkSpeed = stdWalkSpeed;
	}
}
