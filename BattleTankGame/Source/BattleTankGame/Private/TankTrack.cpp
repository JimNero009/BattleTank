// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) { return; }
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp, Warning, TEXT("Added force %s to tank"), *ForceApplied.ToString());
	CurrentThrottle = 0;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	//ApplySidewaysForce();
}

void UTankTrack::ApplySidewaysForce() {	
	// Calculate slip speed
	auto SlipSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work out accleration and apply force
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectingAcceleration = -SlipSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectingAcceleration / 2.0f;
	TankRoot->AddForce(CorrectionForce);
}

