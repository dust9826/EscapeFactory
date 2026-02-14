// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "EFItemDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "EFInventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StackCountText;
	
	void UpdateSlot(const FEFItemStack& NewStack);
};
