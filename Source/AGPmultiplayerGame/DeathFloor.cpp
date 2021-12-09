// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathFloor.h"
#include "AGPmultiplayerGameCharacter.h"

// Sets default values
ADeathFloor::ADeathFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetSimulatePhysics(true);
	RootComponent = staticMesh;
}

// Called when the game starts or when spawned
void ADeathFloor::BeginPlay()
{
	Super::BeginPlay();
	staticMesh->OnComponentHit.AddDynamic(this, &ADeathFloor::OnHit);

}

// Called every frame
void ADeathFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathFloor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAGPmultiplayerGameCharacter* chr = Cast<AAGPmultiplayerGameCharacter>(OtherActor);

	if (chr)
	{
		chr->RespawnPlayer();
	}
}