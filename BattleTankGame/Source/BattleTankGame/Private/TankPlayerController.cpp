// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"

ATank* ATankPlayerController::GetOwnedTank() const {
	return Cast<ATank>(GetPawn());
};


