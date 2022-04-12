// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	this->PrimaryActorTick.bCanEverTick = true;
	this->SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (this->HasAuthority()) {
		this->SetReplicates(true);
		this->SetReplicateMovement(true);
	}

	this->_InitialLocation = this->GetActorLocation();
	this->_WorldTargetLocation = this->GetTransform().TransformPosition(this->RelativeFinalDestination);
	this->_MovingToDestination = true;
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (this->HasAuthority()) {
		this->Move(DeltaSeconds);
	}
}

void AMovingPlatform::Move(const float DeltaSeconds)
{
	FVector CurrentLocation = this->GetActorLocation();

	if (this->_MovingToDestination) {
		this->SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, this->_WorldTargetLocation, DeltaSeconds, this->Speed));
	}
	else {
		this->SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, this->_InitialLocation, DeltaSeconds, this->Speed));
	}

	CurrentLocation = this->GetActorLocation();
	if (CurrentLocation.Equals(this->_WorldTargetLocation)) {
		this->_MovingToDestination = false;
	}
	else if (CurrentLocation.Equals(this->_InitialLocation)) {
		this->_MovingToDestination = true;
	}
}
