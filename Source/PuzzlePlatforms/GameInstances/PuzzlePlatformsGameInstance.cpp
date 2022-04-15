// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "PuzzlePlatforms/MenuSystem/MainMenu.h"

#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer): UGameInstance(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintMenuClass(TEXT("/Game/MenuSystem/WBP_AdvMainMenu"));
	if (BlueprintMenuClass.Class != nullptr) {
		this->MenuClass = BlueprintMenuClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("MenuClass name is %s"), *this->MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::HostGame()
{
	if (this->GetWorld()->GetNetMode() == ENetMode::NM_Client) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Unable to host game as a server"));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting Game"));

	this->GetWorld()->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
}

void UPuzzlePlatformsGameInstance::JoinGame(const FString &IpAddress)
{
	FString TrimmedIp = IpAddress.TrimStartAndEnd();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Joining Game " + TrimmedIp));

	this->GetFirstLocalPlayerController()->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	if (this->CurrentWidget != nullptr) {
		this->CurrentWidget->RemoveFromViewport();
		this->CurrentWidget = nullptr;
	}

	if (this->MenuClass != nullptr) {
		this->CurrentWidget = CreateWidget(this->GetWorld(), this->MenuClass);
		UE_LOG(LogTemp, Warning, TEXT("Before Add to viewport"));
		this->CurrentWidget->AddToViewport();

		if (UMainMenu* MainMenu = Cast<UMainMenu>(this->CurrentWidget)) {
			MainMenu->SetMenuInterface(this);
		}
	}
}
