// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward Declarations
// ====================
class UButton; // #include "Components/Button.h"
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
	UButton* JoinButton;

	UFUNCTION()
	virtual void HandleHostClick();

	UFUNCTION()
	virtual void HandleJoinClick();

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	IMenuInterface* MenuInterface;
};
