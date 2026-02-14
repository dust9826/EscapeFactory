// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractionText;

	void SetInteractionName(FString NewName);
};
