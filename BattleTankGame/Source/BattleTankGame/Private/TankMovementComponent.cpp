// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw) const {

	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
}

void UTankMovementComponent::IntendRotateClockwise(float Throw) const {

	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = (GetOwner()->GetActorForwardVector()).GetSafeNormal();
	auto CosTheta = FVector::DotProduct(AIForwardIntention, TankForward);
	//auto SinTheta = FMath::Sqrt(1 - CosTheta*CosTheta);
	auto SinTheta = FVector::CrossProduct(TankForward,AIForwardIntention).Z;
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *GetOwner()->GetName(), *AIForwardIntention.ToString())
	IntendMoveForward(CosTheta);
	IntendRotateClockwise(SinTheta);
}



