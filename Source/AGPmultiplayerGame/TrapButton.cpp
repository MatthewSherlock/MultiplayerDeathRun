// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapButton.h"
#include "TrapBase.h"
// Sets default values
ATrapButton::ATrapButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetSimulatePhysics(true);
	RootComponent = staticMesh;
}

// Called when the game starts or when spawned
void ATrapButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapButton::ActivateTrap()
{
	if(trapActivated != nullptr)
		trapActivated->UseTrap();
}

