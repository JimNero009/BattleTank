// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT

class UTankAimingComponent;

UCLASS()
class BATTLETANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector & RaycastDirection) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;
	bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXPosition = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYPosition = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
