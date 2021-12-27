// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPickup.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h" //for ActorIterator
#include "AGP_GameState.h" //for gameTime

AJumpPickup::AJumpPickup()
{
	jumpAmount = 2.0f;
}


void AJumpPickup::BeginPlay()
{
	Super::BeginPlay();
}
void AJumpPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
		}
	}
}

void AJumpPickup::UsePickup()
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr)
	{
		GetWorldTimerManager().SetTimer(endEffect, this, &AJumpPickup::PickupEnd, effectTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "used");
		stdJumpHeight = chr->GetCharacterMovement()->JumpZVelocity;
		chr->GetCharacterMovement()->JumpZVelocity = chr->GetCharacterMovement()->JumpZVelocity + jumpAmount;
	}
}

void AJumpPickup::PickupEnd()
{

	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr)
	{
		chr->currPickup = nullptr;
		chr->GetCharacterMovement()->JumpZVelocity = stdJumpHeight;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "TimerEnd");
	}
}
