// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EFInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UEFInteractable : public UInterface {GENERATED_BODY()};

/**
 * 
 */
class ESCAPEFACTORY_API IEFInteractable
{
	GENERATED_BODY()
public:
	virtual void Interact(AActor* Interactor) = 0;
	
	virtual FString GetInteractName() const = 0;
	
	virtual void OnFocused() {}
	virtual void OnUnFocused() {}
};
