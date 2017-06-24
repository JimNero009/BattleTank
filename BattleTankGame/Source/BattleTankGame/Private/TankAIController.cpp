// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"

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
}


