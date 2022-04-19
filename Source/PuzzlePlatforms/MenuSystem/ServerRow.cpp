// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"

bool UServerRow::Initialize()
{
	bool SuperInitializeResult = Super::Initialize();
	ensure(SuperInitializeResult);
	if (!SuperInitializeResult) {
		return false;
	}

	if (this->RowButton != nullptr) {
		this->RowButton->OnClicked.AddDynamic(this, &UServerRow::HandleRowButtonClick);
		this->RowButton->OnHovered.AddDynamic(this, &UServerRow::HandleRowButtonHover);
		this->RowButton->OnUnhovered.AddDynamic(this, &UServerRow::HandleRowButtonUnHover);
	}

	return true;
}

void UServerRow::Setup(UMainMenu* ParentWidget, uint32 RowIndexNum)
{
	this->ParentMenu = ParentWidget;
	this->RowIndex = RowIndexNum;
}

void UServerRow::SetActive()
{
	this->bIsActive = true;
	this->SetRowColor(FColor::Green);
}

void UServerRow::Deactivate()
{
	this->bIsActive = false;
	this->SetRowColor(FColor::White);
}

void UServerRow::HandleRowButtonClick()
{
	if (ensure(this->ParentMenu != nullptr)) {
		this->ParentMenu->SetSelectedRowIndex(this->RowIndex);
	}
}

void UServerRow::HandleRowButtonHover()
{
	if (!this->bIsActive) {
		this->SetRowColor(FColor::Red);
	}
}

void UServerRow::HandleRowButtonUnHover()
{
	if (!this->bIsActive) {
		this->SetRowColor(FColor::White);
	}
}

void UServerRow::SetRowColor(const FColor& Color)
{
	if (this->ServerNameTextBlock != nullptr) {
		FSlateColor ColorConfig = FSlateColor(Color);
		this->ServerNameTextBlock->SetColorAndOpacity(ColorConfig);
	}
}
