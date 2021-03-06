// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void SetPawn(APawn* InPawn) override;

	float AcceptanceRadius = 8000; // how close can the AI tank get to the player?

	UFUNCTION()
	void OnPossessedTankDeath();
};
