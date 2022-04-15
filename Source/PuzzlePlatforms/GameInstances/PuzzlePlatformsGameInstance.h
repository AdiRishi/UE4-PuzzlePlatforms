// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzlePlatforms/MenuSystem/MenuInterface.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec)
	virtual void HostGame() override;

	UFUNCTION(Exec)
	virtual void JoinGame(const FString& IpAddress) override;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void LoadMainMenu();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MenuClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
