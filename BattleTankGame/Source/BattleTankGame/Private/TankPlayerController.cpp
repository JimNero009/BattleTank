// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// moves the tank's barrel towards crosshair s.t. a shot will hit where the crosshair aims
void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation; // Out paramter
	if (GetSightRayHitLocation(OUT HitLocation)) { // has side effect, raytraces and sets the vector
		AimingComponent->AimAt(HitLocation); // delegate the aiming
	}
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	// find the crosshair projection in pixel coords
	int32 SizeXViewport, SizeYViewport;
	GetViewportSize(OUT SizeXViewport, OUT SizeYViewport);
	FVector2D ScreenLocation = FVector2D(SizeXViewport*CrosshairXPosition, SizeYViewport*CrosshairYPosition);

	// de-project it to a ws position
	FVector RaycastDirection;
	if (GetLookDirection(ScreenLocation, RaycastDirection)) {
		GetLookVectorHitLocation(RaycastDirection, OUT OutHitLocation);
	}
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