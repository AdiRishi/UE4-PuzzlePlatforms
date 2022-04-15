// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatforms/GameModes/PuzzlePlatformsGameMode.h"
#include "PuzzlePlatforms/Characters/PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
#if UE_BUILD_SHIPPING
	//this->bUseSeamlessTravel = true;
#endif
}
