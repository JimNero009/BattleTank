// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth = 0; // Initilaised in beginplay
};
