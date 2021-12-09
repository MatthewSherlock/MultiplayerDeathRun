// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"
#include "PickupBase.generated.h"

UCLASS()
class AGPMULTIPLAYERGAME_API APickupBase : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere)
		bool instantKill;
	UPROPERTY(EditAnywhere)
		float effectTime;
	UPROPERTY(EditDefaultsOnly, Category = HitEffects)
		USoundBase* pickupSound;
	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite)
		FTimerHandle endEffect;
};
