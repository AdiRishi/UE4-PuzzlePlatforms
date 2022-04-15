// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"

#include "MovingPlatform.h"

#include "Components/BoxComponent.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;

	this->Mesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->SetRootComponent(Mesh);
	this->Mesh->SetMobility(EComponentMobility::Static);

	this->TriggerBox = this->CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	this->TriggerBox->SetupAttachment(this->RootComponent);
	this->TriggerBox->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	this->TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerBoxOverlapBegin);
	this->TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerBoxOverlapEnd);
}

void APlatformTrigger::OnTriggerBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto Platform : this->ConnectedPlatforms) {
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnTriggerBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Platform : this->ConnectedPlatforms) {
		Platform->RemoveActiveTrigger();
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

