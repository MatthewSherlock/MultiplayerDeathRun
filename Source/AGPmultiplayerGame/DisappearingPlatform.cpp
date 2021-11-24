// Fill out your copyright notice in the Description page of Project Settings.


#include "DisappearingPlatform.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"



ADisappearingPlatform::ADisappearingPlatform()
{
	instantKill = false;
}


void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();
	staticMesh->OnComponentHit.AddDynamic(this, &ADisappearingPlatform::OnHit);

}


void ADisappearingPlatform::UseTrap()
{
	this->Destroy();


}

void ADisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADisappearingPlatform::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);

	if (chr)
	{
	}
}
