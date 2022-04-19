// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "PuzzlePlatforms/MenuSystem/MenuInterface.h"
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

	TSubclassOf<UUserWidget> GetMainMenuClass() const;

	TSubclassOf<UUserWidget> GetInGameMenuClass() const;

	UFUNCTION(Exec)
	virtual void HostGame() override;

	UFUNCTION(Exec)
	virtual void JoinGame(const FString& IpAddress) override;

	UFUNCTION(Exec)
	virtual void JoinGameViaSearchResultIndex(uint32 Index);

	virtual void RefreshGameList();

	UFUNCTION()
	virtual void QuitToMainMenu() override;

	UFUNCTION(Exec)
	virtual void QuitGame() override;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void LoadGameMenu(TSubclassOf<UUserWidget> MenuClass);

private:
	bool bUseLanSession = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InGameMenuClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	bool bCreateOnDestroyRequested = false;

	void CreateSession();
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
};
