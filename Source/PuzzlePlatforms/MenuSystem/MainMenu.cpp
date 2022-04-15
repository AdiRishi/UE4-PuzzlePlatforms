// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): UUserWidget(ObjectInitializer)
{
	this->bIsFocusable = true;
}

bool UMainMenu::Initialize()
{
	bool SuperInitializeResult = Super::Initialize();
	ensure(SuperInitializeResult);
	if (!SuperInitializeResult) {
		return false;
	}

	if (ensure(this->HostButton != nullptr)) {
		this->HostButton->OnClicked.AddDynamic(this, &UMainMenu::HandleHostButtonClick);
	}
	if (ensure(this->JoinMenuButton != nullptr)) {
		this->JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HandleJoinMenuButtonClick);
	}
	if (ensure(this->CancelJoinMenuButton != nullptr)) {
		this->CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HandleCancelButtonClick);
	}
	if (ensure(this->JoinGameButton != nullptr)) {
		this->JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::HandleJoinGameButtonClick);
	}

	APlayerController* PlayerController = this->GetOwningPlayer();
	if (PlayerController != nullptr) {
		FInputModeUIOnly UIInputMode;
		UIInputMode.SetWidgetToFocus(this->TakeWidget());
		UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(UIInputMode);
	}

	return true;

}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	this->MenuInterface = Interface;
}

void UMainMenu::HandleHostButtonClick()
{
	if (this->MenuInterface != nullptr) {
		this->MenuInterface->HostGame();
	}
}

void UMainMenu::HandleJoinMenuButtonClick()
{
	if (ensure(this->MenuSwitcher != nullptr)) {
		this->MenuSwitcher->SetActiveWidgetIndex(1);
	}
}

void UMainMenu::HandleCancelButtonClick()
{
	if (ensure(this->MenuSwitcher != nullptr)) {
		this->MenuSwitcher->SetActiveWidgetIndex(0);
	}
}

void UMainMenu::HandleJoinGameButtonClick()
{
	if (ensure(this->MenuInterface != nullptr) && ensure(this->IpAddressTextBox != nullptr)) {
		this->MenuInterface->JoinGame(this->IpAddressTextBox->GetText().BuildSourceString());
	}
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	APlayerController* PlayerController = this->GetOwningPlayer();
	if (ensure(PlayerController != nullptr)) {
		FInputModeGameOnly GameInputMode;
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(GameInputMode);
	}
}
