// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapBase.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetSimulatePhysics(true);
	RootComponent = staticMesh;
}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	staticMesh->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::OnBeginOverlap);
	staticMesh->OnComponentHit.AddDynamic(this, &ATrapBase::OnHit);
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ATrapBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}