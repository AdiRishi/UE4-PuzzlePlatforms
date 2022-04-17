// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsPlayerController.h"

#include "PuzzlePlatforms/GameInstances/PuzzlePlatformsGameInstance.h"

void APuzzlePlatformsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = this->GetGameInstance();
	if (ensure(GameInstance != nullptr)) {
		this->PuzzlePlatformsGameInstance = Cast<UPuzzlePlatformsGameInstance>(GameInstance);
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Loaded"));
}

void APuzzlePlatformsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (ensure(this->InputComponent != nullptr)) {
		UE_LOG(LogTemp, Warning, TEXT("Setting up input binding"));
		this->InputComponent->BindAction(TEXT("MenuOpen"), EInputEvent::IE_Pressed, this, &APuzzlePlatformsPlayerController::HandleInGameMenuAction);
	}
}

void APuzzlePlatformsPlayerController::SetupInGameMenuBinding()
{
	this->bInGameMenuEnabled = true;
}

void APuzzlePlatformsPlayerController::CloseInGameMenu()
{
	if (this->bInGameMenuEnabled && ensure(this->PuzzlePlatformsGameInstance != nullptr)) {
		this->PuzzlePlatformsGameInstance->LoadGameMenu(nullptr);
		this->bIsMenuOpen = false;
	}
}

void APuzzlePlatformsPlayerController::HandleInGameMenuAction()
{
	if (this->bInGameMenuEnabled && ensure(this->PuzzlePlatformsGameInstance != nullptr)) {
		if (this->bIsMenuOpen) {
			PuzzlePlatformsGameInstance->LoadGameMenu(nullptr);
			this->bIsMenuOpen = false;
		}
		else {
			PuzzlePlatformsGameInstance->LoadGameMenu(PuzzlePlatformsGameInstance->GetInGameMenuClass());
			this->bIsMenuOpen = true;
		}
	}
}
