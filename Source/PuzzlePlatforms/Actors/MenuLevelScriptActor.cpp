// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuLevelScriptActor.h"

#include "PuzzlePlatforms/GameInstances/PuzzlePlatformsGameInstance.h"
#include "PuzzlePlatforms/PlayerControllers/PuzzlePlatformsPlayerController.h"

void AMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	if (this->bShouldSetupMainMenu) {
		this->SetupMainMenu();
	}
	if (this->bShouldSetupInGameMenu) {
		this->SetupInGameMenu();
	}
}

void AMenuLevelScriptActor::SetupMainMenu()
{
	UGameInstance* GameInstance = this->GetGameInstance();
	UPuzzlePlatformsGameInstance* PuzzlePlatformsGameInstance = Cast<UPuzzlePlatformsGameInstance>(GameInstance);
	if (PuzzlePlatformsGameInstance) {
		PuzzlePlatformsGameInstance->LoadGameMenu(PuzzlePlatformsGameInstance->GetMainMenuClass());
	}
}

void AMenuLevelScriptActor::SetupInGameMenu()
{
	APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();
	APuzzlePlatformsPlayerController* PuzzlePlatformsPlayerController = Cast<APuzzlePlatformsPlayerController>(PlayerController);
	if (ensure(PuzzlePlatformsPlayerController != nullptr)) {
		PuzzlePlatformsPlayerController->SetupInGameMenuBinding();
	}
}
