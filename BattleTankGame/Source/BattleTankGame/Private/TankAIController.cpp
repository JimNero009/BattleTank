// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

ATank* ATankAIController::GetControlledTank() const { return  Cast<ATank>(GetPawn()); };

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI controller - begin play"));
	ATank* pPossessedTank = GetControlledTank();
	if (pPossessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed by AI - %s"), *pPossessedTank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed by AI"));
	}
	ATank* pPlayerTank = GetPlayerTank();
	if (pPlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player's tank found - %s"), *pPlayerTank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player's tank not found"));
	}
}

ATank * ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ATank* pPossessedTank = GetControlledTank();
	ATank* pPlayerTank = GetPlayerTank();
	if(pPossessedTank && pPlayerTank){
		// Move towards the player
		// Aim at the player
		pPossessedTank->AimAt(pPlayerTank->GetActorLocation());
		// Fire TODO if ready
		GetControlledTank()->Fire();
	}
}



