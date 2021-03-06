// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	UTankTrack();

private:

	void DriveTrack();

	float CurrentThrottle = 0;

	// max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxForce = 40000 * 2.7; // 2.7 m/s^2 acleration
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

};
