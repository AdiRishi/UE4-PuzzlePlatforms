// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidgetBase.h"
#include "InGameMenu.generated.h"

// Forward Declarations
// ====================
class UButton; // #include "Components/Button.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidgetBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION()
	void HandleCancelButtonClick();

	UFUNCTION()
	void HandleQuitButtonClick();
};
