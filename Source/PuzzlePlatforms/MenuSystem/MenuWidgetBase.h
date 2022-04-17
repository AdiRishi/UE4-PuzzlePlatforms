// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidgetBase.generated.h"

// Forward Declarations
// ====================
class IMenuInterface; // #include "MenuInterface.h

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Setup();

	virtual void Teardown();

	void SetMenuInterface(IMenuInterface* Interface);

protected:
	IMenuInterface* MenuInterface;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	
};
