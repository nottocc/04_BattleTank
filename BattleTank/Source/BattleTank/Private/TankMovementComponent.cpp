// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Vector.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// no need to call Super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), RightThrow, ForwardThrow)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack|| !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO remove double speed from multiple inputs
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Intend move backward throw: %f"), Throw)
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO remove double speed from multiple inputs
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Intend turn left throw: %f"), Throw)
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	// TODO remove double speed from multiple inputs
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw: %f"), Throw)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO remove double speed from multiple inputs
}


