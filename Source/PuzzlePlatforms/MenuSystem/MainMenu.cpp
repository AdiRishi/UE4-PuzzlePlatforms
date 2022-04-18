// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"
#include "ServerRow.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): UMenuWidgetBase(ObjectInitializer)
{
	this->bIsFocusable = true;

	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintServerRowClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (BlueprintServerRowClass.Class != nullptr) {
		this->ServerRowClass = BlueprintServerRowClass.Class;
	}
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
	if (ensure(this->QuitGameButton != nullptr)) {
		this->QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::HandleQuitGameButton);
	}
	if (ensure(this->CancelJoinMenuButton != nullptr)) {
		this->CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HandleCancelButtonClick);
	}
	if (ensure(this->JoinGameButton != nullptr)) {
		this->JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::HandleJoinGameButtonClick);
	}

	this->Setup();
	this->AddToViewport();
	this->SetServerList({});

	return true;

}

void UMainMenu::SetServerList(TArray<FString> ServerList)
{
	if (ensure(this->ServerListScrollBox != nullptr)) {
		this->ServerListScrollBox->ClearChildren();
		if (ServerList.Num() <= 0) {
			UServerRow* ServerRow = CreateWidget<UServerRow>(this->ServerListScrollBox, this->ServerRowClass);
			ServerRow->Setup(this, 0);
			ServerRow->ServerNameTextBlock->SetText(FText::FromString(TEXT("Finding Servers...")));
			this->ServerListScrollBox->AddChild(ServerRow);
		}
		else {
			this->SelectedRowIndex.Reset();
			uint32 Index = 0;
			for (FString& ServerName : ServerList) {
				UServerRow* ServerRow = CreateWidget<UServerRow>(this->ServerListScrollBox, this->ServerRowClass);
				ServerRow->Setup(this, Index);
				ServerRow->ServerNameTextBlock->SetText(FText::FromString(ServerName));
				this->ServerListScrollBox->AddChild(ServerRow);
				Index++;
			}
		}
	}
}

void UMainMenu::SetSelectedRowIndex(uint32 RowIndex)
{
	this->SelectedRowIndex = RowIndex;
	UE_LOG(LogTemp, Warning, TEXT("Selected rowindex is %d"), RowIndex);
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
		this->MenuSwitcher->SetActiveWidgetIndex(ESubMenu::JoinGameMenu);
	}
}

void UMainMenu::HandleQuitGameButton()
{
	if (ensure(this->MenuInterface != nullptr)) {
		this->MenuInterface->QuitGame();
	}
}

void UMainMenu::HandleCancelButtonClick()
{
	if (ensure(this->MenuSwitcher != nullptr)) {
		this->MenuSwitcher->SetActiveWidgetIndex(ESubMenu::MainMenu);
	}
}

void UMainMenu::HandleJoinGameButtonClick()
{
	if (ensure(this->MenuInterface != nullptr) && ensure(this->IpAddressTextBox != nullptr)) {
		this->MenuInterface->JoinGame(this->IpAddressTextBox->GetText().BuildSourceString());
	}
}
