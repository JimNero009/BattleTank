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
}

ATank * ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerPawn)) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ATank* pPossessedTank = GetControlledTank();
	ATank* pPlayerTank = GetPlayerTank();
	if (!ensure(pPossessedTank && pPlayerTank)) { return; }
	// Move towards the player
	MoveToActor(pPlayerTank, AcceptanceRadius); // TODO check radius is in cm
	// Aim at the player
	pPossessedTank->AimAt(pPlayerTank->GetActorLocation());
	GetControlledTank()->Fire();
}



