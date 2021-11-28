// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Use a Box for the spawn volume.
	whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	whereToSpawn->SetBoxExtent(FVector(200.0, 200.0, 10.0));
	whereToSpawn->SetupAttachment(RootComponent);
}

FVector APickupSpawner::getRandomPtInVolume() {
	FVector spawnOrigin = whereToSpawn->Bounds.Origin;
	FVector spawnExtent = whereToSpawn->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}
// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupSpawner::SpawnPickup(TSubclassOf<AActor> pickup)
{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector spawnLoc = getRandomPtInVolume();
		FRotator rot = FRotator::ZeroRotator;
		AActor* a = GetWorld()->SpawnActor<AActor>(pickup, spawnLoc, rot, spawnParams);
}

