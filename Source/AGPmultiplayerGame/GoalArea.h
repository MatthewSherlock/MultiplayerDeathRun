// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalArea.generated.h"

UCLASS()
class AGPMULTIPLAYERGAME_API AGoalArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* collisionComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* staticMeshComponent;
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<int>playerIDsAtGoal;
	void addToPlayerIDsAtGoal(int ID);
	int getNumOfPlayersAtGoal();

};
