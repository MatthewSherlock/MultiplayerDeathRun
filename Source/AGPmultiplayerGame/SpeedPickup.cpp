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
	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpeedPickup::OnBeginOverlap);
}
void ASpeedPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);
	if (chr)
	{
		chr->GrabPickup(this);

		if (pickupSound)
			UGameplayStatics::PlaySoundAtLocation(this, pickupSound, GetActorLocation());

		Destroy();
	}
}

void ASpeedPickup::UsePickup() 
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr) 
	{  
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "used");
		stdWalkSpeed = chr->GetCharacterMovement()->MaxWalkSpeed;
		chr->GetCharacterMovement()->MaxWalkSpeed = chr->GetCharacterMovement()->MaxWalkSpeed + speedAmount;
		FTimerHandle endEffect;
		GetWorldTimerManager().SetTimer(endEffect, this, &ASpeedPickup::PickupEnd, 2.0f, false);
	}
}

void ASpeedPickup::PickupEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "TimerEnd");

	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (chr)
	{
		chr->GetCharacterMovement()->MaxWalkSpeed = stdWalkSpeed;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "TimerEnd");
	}
}
