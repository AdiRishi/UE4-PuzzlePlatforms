// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	const int32 TotalPlayers = this->GetNumPlayers();
	if (TotalPlayers >= 3) {
		UWorld* World = this->GetWorld();
		if (ensure(World != nullptr)) {
			this->bUseSeamlessTravel = true;
			World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
		}
	}
}
