// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch(float Speed);

	
	

private:
	UProjectileMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileDamage = 20;


	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void OnTimerExpire();
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestroyDelay = 10;

	
};
