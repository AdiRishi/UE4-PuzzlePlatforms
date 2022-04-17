// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "PuzzlePlatforms/MenuSystem/MenuWidgetBase.h"

#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer): UGameInstance(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintMainMenuClass(TEXT("/Game/MenuSystem/WBP_AdvMainMenu"));
	if (BlueprintMainMenuClass.Class != nullptr) {
		this->MainMenuClass = BlueprintMainMenuClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintInGameMenuClass(TEXT("/Game/MenuSystem/WBP_AdvInGameMenu"));
	if (BlueprintInGameMenuClass.Class != nullptr) {
		this->InGameMenuClass = BlueprintInGameMenuClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
}

TSubclassOf<UUserWidget> UPuzzlePlatformsGameInstance::GetMainMenuClass() const
{
	return this->MainMenuClass;
}

TSubclassOf<UUserWidget> UPuzzlePlatformsGameInstance::GetInGameMenuClass() const
{
	return this->InGameMenuClass;
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

void UPuzzlePlatformsGameInstance::QuitToMainMenu()
{
	APlayerController* PlayerController = this->GetFirstLocalPlayerController();
	if (ensure(PlayerController != nullptr)) {
		PlayerController->ClientTravel(TEXT("/Game/MenuSystem/MainMenuLevel"), ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this->GetWorld(), this->GetFirstLocalPlayerController(), EQuitPreference::Quit, false);
}

void UPuzzlePlatformsGameInstance::LoadGameMenu(TSubclassOf<UUserWidget> MenuClass)
{
	if (this->CurrentWidget != nullptr) {
		if (UMenuWidgetBase* MenuWidgetInstance = Cast<UMenuWidgetBase>(this->CurrentWidget)) {
			MenuWidgetInstance->Teardown();
		}
		this->CurrentWidget->RemoveFromViewport();
		this->CurrentWidget = nullptr;
	}

	if (MenuClass != nullptr) {
		this->CurrentWidget = CreateWidget(this->GetWorld(), MenuClass);

		if (UMenuWidgetBase* MenuWidgetInstance = Cast<UMenuWidgetBase>(this->CurrentWidget)) {
			MenuWidgetInstance->SetMenuInterface(this);
		}
	}
}
