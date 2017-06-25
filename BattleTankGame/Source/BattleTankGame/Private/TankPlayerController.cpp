// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"

#define OUT

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
	FVector HitLocation; // Out paramter
	if (GetSightRayHitLocation(OUT HitLocation)) { // has side effect, raytraces and sets the vector
		
	// Get player's space location
	// Move barrel towards 
	}
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT OutHitLocation) const {
	// find the crosshair projection in pixel coords
	int32 SizeXViewport, SizeYViewport;
	GetViewportSize(OUT SizeXViewport, OUT SizeYViewport);
	FVector2D ScreenLocation = FVector2D(SizeXViewport*CrosshairXPosition, SizeYViewport*CrosshairYPosition);

	// de-project it to a ws position
	FVector RaycastDirection;
	if (GetLookDirection(ScreenLocation, RaycastDirection)) {
		GetLookVectorHitLocation(RaycastDirection, OUT OutHitLocation);
		UE_LOG(LogTemp, Warning, TEXT("HitLocation at %s"),*OutHitLocation.ToString());
	}
	
	// line trace along that direction
	// see what we hit, up to some max range
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& RaycastDirection) const {
	FVector WorldCameraDirection; // not used, but needs to be passed
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldCameraDirection, OUT RaycastDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector RaycastDirection, FVector& HitLocation) const {
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FHitResult OutHit;
	if (GetWorld()->LineTraceSingleByChannel(OutHit,
		CameraLocation,
		CameraLocation + RaycastDirection*LineTraceRange,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = OutHit.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}