// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidgetBase.h"

void UMenuWidgetBase::Setup()
{
	APlayerController* PlayerController = this->GetOwningPlayer();
	if (PlayerController != nullptr) {
		FInputModeUIOnly UIInputMode;
		UIInputMode.SetWidgetToFocus(this->TakeWidget());
		UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(UIInputMode);
	}
}

void UMenuWidgetBase::Teardown()
{
	APlayerController* PlayerController = this->GetOwningPlayer();
	if (ensure(PlayerController != nullptr)) {
		FInputModeGameOnly GameInputMode;
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(GameInputMode);
	}
}

void UMenuWidgetBase::SetMenuInterface(IMenuInterface* Interface)
{
	if (ensure(Interface != nullptr)) {
		this->MenuInterface = Interface;
	}
}

void UMenuWidgetBase::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	this->Teardown();
}
