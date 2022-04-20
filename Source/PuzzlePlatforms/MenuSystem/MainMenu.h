// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "MainMenu.generated.h"

// Forward Declarations
// ====================
class UButton; // #include "Components/Button.h"
class UWidgetSwitcher; // #include "Components/WidgetSwitcher.h"
class UEditableTextBox; // #include "Components/EditableTextBox.h"
class IMenuInterface; // #include "MenuInterface.h
class UScrollBox; // #include "Components/ScrollBox.h"

USTRUCT()
struct FServerData {
	GENERATED_BODY()

	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
	FString ServerId;

	FServerData() : CurrentPlayers(0), MaxPlayers(0), HostUsername(), ServerId() {}
	FServerData(uint16 NumMaxPlayers, uint16 NumCurrentPlayers, FString ServerHostUsername, FString ServerIdentifier)
		: CurrentPlayers(NumCurrentPlayers), MaxPlayers(NumMaxPlayers),
		HostUsername(ServerHostUsername), ServerId(ServerIdentifier) {}
};

UENUM()
enum ESubMenu
{
	MainMenu = 0 UMETA(DisplayName = "MainMenu"),
	JoinGameMenu = 1 UMETA(DisplayName = "JoinGameMenu"),
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	void SetServerList(const TArray<FServerData>& ServerList);

	void SetSelectedRowIndex(uint32 RowIndex);

	virtual void Teardown() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelJoinMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* IpAddressTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* ServerListScrollBox;

	UFUNCTION()
	virtual void HandleHostButtonClick();

	UFUNCTION()
	virtual void HandleJoinMenuButtonClick();

	UFUNCTION()
	virtual void HandleQuitGameButton();

	UFUNCTION()
	virtual void HandleCancelButtonClick();

	UFUNCTION()
	virtual void HandleJoinGameButtonClick();

	UFUNCTION()
	virtual void HandleSessionRefreshTimer();

private:
	TSubclassOf<UUserWidget> ServerRowClass;

	TOptional<uint32> SelectedRowIndex;

	FTimerHandle SessionRefreshTimerHandle;

	TOptional<uint32> LastActiveIndex;
};
