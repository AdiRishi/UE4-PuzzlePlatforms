// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

void UPuzzlePlatformsGameInstance::HostGame()
{
	if (this->GetWorld()->GetNetMode() == ENetMode::NM_Client) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Unable to host game as a server"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Hosting Game"));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting Game"));

	this->GetWorld()->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
}

void UPuzzlePlatformsGameInstance::JoinGame(FString &IpAddress)
{
	UE_LOG(LogTemp, Warning, TEXT("Joining Game"));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Joining Game " + IpAddress));

	this->GetFirstLocalPlayerController()->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute);
}
