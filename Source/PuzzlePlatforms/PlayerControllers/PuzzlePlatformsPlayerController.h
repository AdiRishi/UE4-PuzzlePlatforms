// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzlePlatformsPlayerController.generated.h"

// Forward Declarations
class UPuzzlePlatformsGameInstance; // #include "PuzzlePlatforms/GameInstances/PuzzlePlatformsGameInstance.h";

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API APuzzlePlatformsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetupInGameMenuBinding();

	void CloseInGameMenu();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void HandleInGameMenuAction();

	bool bIsMenuOpen = false;
	bool bInGameMenuEnabled = false;

	UPROPERTY()
	UPuzzlePlatformsGameInstance* PuzzlePlatformsGameInstance;
};
