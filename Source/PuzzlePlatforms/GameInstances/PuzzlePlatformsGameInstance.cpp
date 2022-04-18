// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "PuzzlePlatforms/MenuSystem/MenuWidgetBase.h"
#include "PuzzlePlatforms/MenuSystem/MainMenu.h"

#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer): UGameInstance(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintMainMenuClass(TEXT("/Game/MenuSystem/WBP_AdvMainMenu"));
	if (BlueprintMainMenuClass.Class != nullptr) {
		this->MainMenuClass = BlueprintMainMenuClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> BlueprintInGameMenuClass(TEXT("/Game/MenuSystem/WBP_AdvInGameMenu"));
	if (BlueprintInGameMenuClass.Class != nullptr) {
		this->InGameMenuClass = BlueprintInGameMenuClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		this->SessionInterface = Subsystem->GetSessionInterface();
		if (this->SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Found Session Interface"));
			this->SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			this->SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			this->SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);

			this->SessionSearch = MakeShareable(new FOnlineSessionSearch());
			this->SessionSearch->bIsLanQuery = true;
			//this->SessionSearch->QuerySettings.Set();
			SessionInterface->FindSessions(0, this->SessionSearch.ToSharedRef());
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Subsystem found"));
	}
}

TSubclassOf<UUserWidget> UPuzzlePlatformsGameInstance::GetMainMenuClass() const
{
	return this->MainMenuClass;
}

TSubclassOf<UUserWidget> UPuzzlePlatformsGameInstance::GetInGameMenuClass() const
{
	return this->InGameMenuClass;
}

void UPuzzlePlatformsGameInstance::HostGame()
{
	if (this->GetWorld()->GetNetMode() == ENetMode::NM_Client) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Unable to host game as a server"));
		return;
	}

	if (this->SessionInterface.IsValid()) {
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
		if (ExistingSession == nullptr) {
			this->CreateSession();
		}
		else {
			this->bCreateOnDestroyRequested = true;
			this->SessionInterface->DestroySession(NAME_GameSession);
		}
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bShouldAdvertise = true;

	if (this->SessionInterface.IsValid()) {
		if (!this->SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings)) {
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Unable to host game as a server"));
		}
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) {
	if (bWasSuccessful) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Hosting Game"));

		this->GetWorld()->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Game Hosting failed - session creation failure"));
	}
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		if (this->bCreateOnDestroyRequested) {
			this->CreateSession();
			this->bCreateOnDestroyRequested = false;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Session destruction failed"));
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	TArray<FString> ServerList;
	if (bWasSuccessful && this->SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Successfuly found sessions"));
		for (FOnlineSessionSearchResult SearchResult : this->SessionSearch->SearchResults) {
			ServerList.Add(SearchResult.GetSessionIdStr());
			UE_LOG(LogTemp, Warning, TEXT("Found session %s"), *SearchResult.GetSessionIdStr());
		}

		if (UMainMenu* MainMenu = Cast<UMainMenu>(this->CurrentWidget)) {
			MainMenu->SetServerList(ServerList);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Find sessions failed"));
	}
}

void UPuzzlePlatformsGameInstance::JoinGame(const FString &IpAddress)
{
	FString TrimmedIp = IpAddress.TrimStartAndEnd();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Joining Game " + TrimmedIp));

	this->GetFirstLocalPlayerController()->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitToMainMenu()
{
	APlayerController* PlayerController = this->GetFirstLocalPlayerController();
	if (ensure(PlayerController != nullptr)) {
		PlayerController->ClientTravel(TEXT("/Game/MenuSystem/MainMenuLevel"), ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this->GetWorld(), this->GetFirstLocalPlayerController(), EQuitPreference::Quit, false);
}

void UPuzzlePlatformsGameInstance::LoadGameMenu(TSubclassOf<UUserWidget> MenuClass)
{
	if (this->CurrentWidget != nullptr) {
		if (UMenuWidgetBase* MenuWidgetInstance = Cast<UMenuWidgetBase>(this->CurrentWidget)) {
			MenuWidgetInstance->Teardown();
		}
		this->CurrentWidget->RemoveFromViewport();
		this->CurrentWidget = nullptr;
	}

	if (MenuClass != nullptr) {
		this->CurrentWidget = CreateWidget(this->GetWorld(), MenuClass);

		if (UMenuWidgetBase* MenuWidgetInstance = Cast<UMenuWidgetBase>(this->CurrentWidget)) {
			MenuWidgetInstance->SetMenuInterface(this);
		}
	}
}
