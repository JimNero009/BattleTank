// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO does this need to tick?

	//Barrel = GetOwner()->GetComponentByClass<UTankBarrel>();
	//Turret = GetOwner()->GetComponentByClass<UTankTurret>();

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation) {	
	//UE_LOG(LogTemp, Warning, TEXT("AimAt called!"));
	if (!ensure(Barrel)) { return; }	
	if (!ensure(Turret)) { return; }
	
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FirePoint"));
	//UE_LOG(LogTemp, Warning, TEXT("Start location is %s"), *StartLocation.ToString())
	// Calculate the LaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity, StartLocation, OutHitLocation, FireSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s, firing at %f"), *(GetOwner()->GetName()), *OutHitLocation.ToString(), *Barrel->GetComponentLocation().ToString(), Speed);
		//UE_LOG(LogTemp, Warning, TEXT("Aiming vector is %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Solution found! Calling MoveBarrel."));
		MoveBarrelTowards(AimDirection);
	}
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Decide how we need to rotate based on where we are now and where we need to be
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateAroundZ(DeltaRotator.Yaw);
}

