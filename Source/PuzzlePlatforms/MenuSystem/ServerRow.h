// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

// Forward Declarations
class UMainMenu; // #include "MainMenu.h"
class UTextBlock; // #include "Components/TextBlock.h"
class UButton; // #include "Components/Button.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void Setup(UMainMenu* Parent, uint32 RowIndex);

	void SetActive();

	void Deactivate();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ServerNameTextBlock;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* RowButton;

private:
	UFUNCTION()
	void HandleRowButtonClick();

	UFUNCTION()
	void HandleRowButtonHover();

	UFUNCTION()
	void HandleRowButtonUnHover();

	void SetRowColor(const FColor &Color);

	UMainMenu* ParentMenu;
	uint32 RowIndex;
	bool bIsActive;
};
