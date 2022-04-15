// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"

#include "Components/Button.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): UUserWidget(ObjectInitializer)
{
	this->bIsFocusable = true;
}

bool UMainMenu::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("In Initialize"));
	bool SuperInitializeResult = Super::Initialize();
	ensure(SuperInitializeResult);
	if (!SuperInitializeResult) {
		return false;
	}

	this->HostButton->OnClicked.AddDynamic(this, &UMainMenu::HandleHostClick);
	this->JoinButton->OnClicked.AddDynamic(this, &UMainMenu::HandleJoinClick);

	APlayerController* PlayerController = this->GetOwningPlayer();
	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(this->TakeWidget());
	UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(UIInputMode);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	this->MenuInterface = Interface;
}

void UMainMenu::HandleHostClick()
{
	if (this->MenuInterface != nullptr) {
		this->MenuInterface->HostGame();
	}
}

void UMainMenu::HandleJoinClick()
{
	if (this->MenuInterface != nullptr) {
		this->MenuInterface->JoinGame("");
	}
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	APlayerController* PlayerController = this->GetOwningPlayer();
	FInputModeGameOnly GameInputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(GameInputMode);
}
