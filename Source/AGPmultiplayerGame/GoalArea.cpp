// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalArea.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h" //for effects
#include "AGPmultiplayerGameCharacter.h"
#include "Kismet/GameplayStatics.h" //for radial dmg
#include "Engine/Engine.h" //for log & debug msg
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"

// Sets default values
AGoalArea::AGoalArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("collisionComponent"));
	RootComponent = collisionComponent;
	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComponent"));
	staticMeshComponent->SetupAttachment(RootComponent);
	staticMeshComponent->SetCollisionProfileName("OverlapAll");
	bReplicates = true;

}

// Called when the game starts or when spawned
void AGoalArea::BeginPlay()
{
	Super::BeginPlay();
	collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoalArea::OnBeginOverlap);
}

// Called every frame
void AGoalArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalArea::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);

	if (chr && chr->IsLocallyControlled()) {
		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap chr = %s"), *chr->GetName());

		TArray<AActor*> Result; //Store ALL players at Goal
		GetOverlappingActors(Result, AAGPmultiplayerGameCharacter::StaticClass());
		for (int i = 0; i < Result.Num(); i++) {
			chr = Cast<AAGPmultiplayerGameCharacter>(Result[i]);
			addToPlayerIDsAtGoal(chr->GetPlayerID());
		}
		chr->updateGoalArea(this, chr->GetPlayerID());
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Not ALL Colours have been collected!"));
}

void AGoalArea::addToPlayerIDsAtGoal(int ID)
{
	for (int i = 0; i < playerIDsAtGoal.Num(); i++) {
		if (playerIDsAtGoal[i] == ID)
			return;
	}
	playerIDsAtGoal.Add(ID);
}

int AGoalArea::getNumOfPlayersAtGoal()
{
	return playerIDsAtGoal.Num();
}





