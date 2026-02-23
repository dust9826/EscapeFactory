// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFItemDataAsset.h"
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
	
	void ConnectInventory(UEFInventoryComponent* InventoryComponent);
	
	void RefreshSlot(int32 SlotIndex, const FEFItemStack& ItemStack);
	
	void DetachInventory();
	
public:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGrid;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UEFInventorySlotWidget> SlotWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 SlotsPerRow = 5;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	UEFInventoryComponent* SourceInventoryComponent;
	
	FDelegateHandle InventoryUpdateHandle;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<UEFInventorySlotWidget*> SlotWidgets;
};
