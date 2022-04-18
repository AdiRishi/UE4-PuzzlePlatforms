// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

#include "MenuInterface.h"
#include "PuzzlePlatforms/PlayerControllers/PuzzlePlatformsPlayerController.h"

UInGameMenu::UInGameMenu(const FObjectInitializer& ObjectInitializer) : UMenuWidgetBase(ObjectInitializer)
{
	this->bIsFocusable = true;
}

bool UInGameMenu::Initialize()
{
	bool SuperInitialize = Super::Initialize();
	if (!ensure(SuperInitialize != false)) {
		return false;
	}

	if (ensure(this->CancelButton != nullptr)) {
		this->CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::HandleCancelButtonClick);
	}

	if (ensure(this->QuitButton != nullptr)) {
		this->QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::HandleQuitButtonClick);
	}

	this->Setup();
	this->AddToViewport();

	return true;
}

void UInGameMenu::HandleCancelButtonClick()
{
	APlayerController* PlayerController = this->GetOwningPlayer();
	if (ensure(PlayerController != nullptr)) {
		if (APuzzlePlatformsPlayerController* PuzzlePlatformsPlayerController = Cast<APuzzlePlatformsPlayerController>(PlayerController)) {
			PuzzlePlatformsPlayerController->CloseInGameMenu();
		}
	}
}

void UInGameMenu::HandleQuitButtonClick()
{
	if (ensure(this->MenuInterface != nullptr)) {
		this->MenuInterface->QuitToMainMenu();
	}
}
