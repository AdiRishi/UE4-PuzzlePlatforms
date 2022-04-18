// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "MainMenu.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UServerRow::Initialize()
{
	bool SuperInitializeResult = Super::Initialize();
	ensure(SuperInitializeResult);
	if (!SuperInitializeResult) {
		return false;
	}

	this->RowButton->OnClicked.AddDynamic(this, &UServerRow::HandleRowButtonClick);

	return true;
}

void UServerRow::Setup(UMainMenu* ParentWidget, uint32 RowIndexNum)
{
	this->ParentMenu = ParentWidget;
	this->RowIndex = RowIndexNum;
}

void UServerRow::HandleRowButtonClick()
{
	if (ensure(this->ParentMenu != nullptr)) {
		this->ParentMenu->SetSelectedRowIndex(this->RowIndex);
	}
}
