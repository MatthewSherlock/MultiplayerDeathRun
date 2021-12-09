// Copyright Epic Games, Inc. All Rights Reserved.

#include "AGPmultiplayerGameCharacter.h"
#include "AGPmultiplayerGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h" //for log & debug msg
#include "Engine/World.h"
#include "PickupBase.h"
#include "TrapBase.h"
#include "GameFramework/PlayerState.h"
#include "TrapButton.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AAGPmultiplayerGameCharacter

AAGPmultiplayerGameCharacter::AAGPmultiplayerGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	grabDistance = 500.0f;
	health = 100.0f;
	maxLives = 3;
}

void AAGPmultiplayerGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


	currLives = maxLives;
	spawnLoc = GetActorLocation();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAGPmultiplayerGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AAGPmultiplayerGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAGPmultiplayerGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAGPmultiplayerGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAGPmultiplayerGameCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAGPmultiplayerGameCharacter::Interact);
	PlayerInputComponent->BindAction("UsePickup", IE_Pressed, this, &AAGPmultiplayerGameCharacter::UsePickup);

}

void AAGPmultiplayerGameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AAGPmultiplayerGameCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AAGPmultiplayerGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAGPmultiplayerGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAGPmultiplayerGameCharacter::Interact()
{
	FVector startLoc = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector endLoc = startLoc + GetFirstPersonCameraComponent()->GetForwardVector() * grabDistance;
	FCollisionQueryParams TraceParams(FName(TEXT("PickingTrace")), true, this);
	TraceParams.bTraceComplex = true;

	GetWorld()->LineTraceSingleByChannel(objHit, startLoc, endLoc, ECC_Visibility, TraceParams); //trace 
	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Blue, false, 1.0f, 0, 2.0f);
	ATrapButton* button = Cast<ATrapButton>(objHit.Actor);
	if (button)
	{
		if (IsLocallyControlled())
			if (GetLocalRole() == ROLE_Authority)
			{
				MC_ActivateTrap(button);
			}
			else
				ServerActivateTrap(button);

	}


}

void AAGPmultiplayerGameCharacter::UsePickup()
{
	if (currPickup != nullptr) {
		currPickup->UsePickup();
	}


}

void AAGPmultiplayerGameCharacter::GrabPickup(APickupBase* pb)
{
	if (currPickup == nullptr && pb)
	{
		currPickup = pb;
	}
}

void AAGPmultiplayerGameCharacter::MC_ActivateTrap_Implementation(AActor* button)
{
	ATrapButton* Button = Cast<ATrapButton>(button);
	if (Button) 
	{
		Button->ActivateTrap();
	}

}

void AAGPmultiplayerGameCharacter::ServerActivateTrap_Implementation(AActor* button)
{
	MC_ActivateTrap(button);
}

void AAGPmultiplayerGameCharacter::MC_GameOver_Implementation(bool hasWon, int winID) {
	gameOverBPImplemEvent(hasWon, winID);
}
void AAGPmultiplayerGameCharacter::MC_GameOverNoLives_Implementation(bool hasLost, int lossID) {
	gameOverNoLivesBPImplemEvent(hasLost, lossID);
}

void AAGPmultiplayerGameCharacter::ServerUpdateGoal_Implementation(AGoalArea* goal, int ID) {
	updateGoal(goal, ID);
}

bool AAGPmultiplayerGameCharacter::ServerUpdateGoal_Validate(AGoalArea* goal, int ID) {
	return true;
}

void AAGPmultiplayerGameCharacter::updateGoal(AGoalArea* goal, int ID) {
	AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());
	if (gm)  
		gm->chkForWin(goal, ID);
}

void AAGPmultiplayerGameCharacter::updateGoalArea(AGoalArea* goal, int ID) {
	if (GetLocalRole() == ROLE_Authority)
		updateGoal(goal, ID);
	else
		ServerUpdateGoal(goal, ID);
}

int AAGPmultiplayerGameCharacter::GetPlayerID() {
	APlayerState* ps = GetPlayerState(); 
	return ps->GetPlayerId(); 
}

void AAGPmultiplayerGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAGPmultiplayerGameCharacter::RespawnPlayer()
{
	if (currLives > 0)
	{
		currLives -= 1;
		SetActorLocation(spawnLoc);
	}
	if (currLives <= 0)
	{
		AAGPmultiplayerGameGameMode* gm = Cast<AAGPmultiplayerGameGameMode>(GetWorld()->GetAuthGameMode());
		if (gm) {

			gm->chkForDeathLoss(true, GetPlayerID());
		}
	}
}
