// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"

ATank* ATankPlayerController::GetControlledTank() const { return  Cast<ATank>(GetPawn()); };

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player controller - begin play"));
	ATank* pPossessedTank = GetControlledTank();
	if (pPossessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed - %s"), *pPossessedTank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// moves the tank's barrel towards crosshair s.t. a shot will hit where the crosshair aims
void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }
	// Get player's space location
	// Move barrel towards 
	return;
}