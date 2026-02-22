// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFInventoryWindowWidget.generated.h"

class UEFInventorySlotWidget;
class UEFInventoryComponent;
/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFInventoryWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGrid;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UEFInventorySlotWidget> SlotWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 SlotsPerRow = 5;
	
	void RefreshInventory(const UEFInventoryComponent* InventoryComponent);
};
