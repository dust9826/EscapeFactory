// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFRecipeSelectWidget.generated.h"

class AEFMachineBase;
class UEFRecipeDataAsset;
class UEFInventorySlotWidget;
/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFRecipeSelectWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	
	void RefreshSlots(AEFMachineBase* MachineBase);
	
public:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGrid;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UEFInventorySlotWidget> SlotWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 SlotsPerRow = 5;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	AEFMachineBase* MachineBaseSource;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<UEFInventorySlotWidget*> SlotWidgets;
};
