// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "GameFramework/PlayerController.h"
#include "EFPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS(abstract, config="Game")
class ESCAPEFACTORY_API AEFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AEFPlayerController();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
};
