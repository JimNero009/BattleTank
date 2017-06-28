// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "UObject/UObjectGlobals.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector OutHitLocation) {
	if (TankAimingComponent) {
		TankAimingComponent->AimAt(OutHitLocation, FireSpeed);
	}
	return;
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Tank firing!"));

	if (!Barrel) { return; }
	//Spawn projectile at socket location
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("FirePoint")), Barrel->GetSocketRotation(FName("FirePoint")));
}

