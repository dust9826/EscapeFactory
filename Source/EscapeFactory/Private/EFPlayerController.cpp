// Fill out your copyright notice in the Description page of Project Settings.


#include "EFPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EscapeFactoryCameraManager.h"

AEFPlayerController::AEFPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AEscapeFactoryCameraManager::StaticClass();
}

void AEFPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AEFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
