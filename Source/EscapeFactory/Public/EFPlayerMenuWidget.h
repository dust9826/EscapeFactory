// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFPlayerMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFPlayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UEFInventoryWindowWidget* PlayerInventoryWidget;
	
	
};
