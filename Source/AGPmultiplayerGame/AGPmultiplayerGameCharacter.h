// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PushWall.h"
#include "GoalArea.h"
#include "AGPmultiplayerGameGameMode.h"
#include "AGPmultiplayerGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AAGPmultiplayerGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

public:
	AAGPmultiplayerGameCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float grabDistance;

	FHitResult objHit;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AAGPmultiplayerGameProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

protected:
	
	/** Fires a projectile. */
//	void OnFire();

	/** Resets HMD orientation and position in VR. */
//	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	//void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	//USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		class APickupBase* currPickup;

	UPROPERTY(BlueprintReadWrite)
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	float currScore;


	void Interact();
	void UsePickup();
	void GrabPickup(class APickupBase* pb);

	UFUNCTION(NetMulticast, Reliable)
		void MC_ActivateTrap(AActor* button);
	void MC_ActivateTrap_Implementation(AActor* button);

	UFUNCTION(Server, Reliable)
		void ServerActivateTrap(AActor* button);
	void ServerActivateTrap_Implementation(AActor* button);

	UFUNCTION(NetMulticast, Reliable)
		void MC_GameOver(bool hasWon, int winID);
	void MC_GameOver_Implementation(bool hasWon, int winID);

	UFUNCTION(NetMulticast, Reliable)
		void MC_GameOverNoLives(bool hasLost, int lossID);
	void MC_GameOverNoLives_Implementation(bool hasLost, int lossID);

	UFUNCTION(BlueprintImplementableEvent)
		void gameOverBPImplemEvent(bool hasWon, int winID);
	UFUNCTION(BlueprintImplementableEvent)
		void gameOverNoLivesBPImplemEvent(bool hasLost, int LossID);
	int GetPlayerID();
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateGoal(AGoalArea* goal, int ID);
	void ServerUpdateGoal_Implementation(AGoalArea* goal, int ID);
	bool ServerUpdateGoal_Validate(AGoalArea* goal, int ID);
	void updateGoal(AGoalArea* goal, int ID); //change attribute value on Server
	void updateGoalArea(AGoalArea* goal, int ID); //called by client / server
	virtual void Tick(float DeltaTime) override;
	void RespawnPlayer();
	int maxLives;
	UPROPERTY(BlueprintReadWrite)
		int currLives;

	FVector spawnLoc;
};

