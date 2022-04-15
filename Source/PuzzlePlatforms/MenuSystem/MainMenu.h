// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward Declarations
// ====================
class UButton; // #include "Components/Button.h"
class UWidgetSwitcher; // #include "Components/WidgetSwitcher.h"
class UEditableTextBox; // #include "Components/EditableTextBox.h"
class IMenuInterface; // #include "MenuInterface.h

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void SetMenuInterface(IMenuInterface* Interface);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelJoinMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* IpAddressTextBox;

	UFUNCTION()
	virtual void HandleHostButtonClick();

	UFUNCTION()
	virtual void HandleJoinMenuButtonClick();

	UFUNCTION()
	virtual void HandleCancelButtonClick();

	UFUNCTION()
	virtual void HandleJoinGameButtonClick();

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	IMenuInterface* MenuInterface;
};
