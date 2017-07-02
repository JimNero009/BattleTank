// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

}

void UTankAimingComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation) {	
	if (!ensure(Barrel)) { return; }	
	if (!ensure(Turret)) { return; }
	
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FirePoint"));
	// Calculate the LaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity, StartLocation, OutHitLocation, FireSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
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

void UTankAimingComponent::Fire() {

	
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (CurrentState != EFiringStatus::Reloading) {
		//Spawn projectile at socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("FirePoint")), Barrel->GetSocketRotation(FName("FirePoint")));
		Projectile->Launch(FireSpeed); 
		
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) {
		CurrentState = EFiringStatus::Reloading;
	} // TODO handle all other states
}

