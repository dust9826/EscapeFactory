// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "EFItemDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "EFInventorySlotWidget.generated.h"

class UEFInventoryComponent;
/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;	
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	
	void SetupSlot(UEFInventoryComponent* SourceInv, int32 Index);
	
	void UpdateSlot(const FEFItemStack& NewStack);
	
	FEFItemStack& GetItemStack();

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StackCountText;
	
private:
	UPROPERTY()
	UEFInventoryComponent* SourceInventory;
	
	UPROPERTY()
	int32 SlotIndex;
	
public:
	UEFInventoryComponent* GetSourceInventory() const { return SourceInventory; }
	int32 GetSlotIndex() const { return SlotIndex; }
};
