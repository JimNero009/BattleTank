// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) const {
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return;  }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	// TODO stop user from using both inputs to double the speed
}
