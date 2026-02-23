// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventoryWindowWidget.h"

#include "EFInventoryComponent.h"
#include "EFInventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UEFInventoryWindowWidget::ConnectInventory(UEFInventoryComponent* InventoryComponent)
{
	if (InventoryComponent != nullptr)
		DetachInventory();
	
	EFCHECK(nullptr != ItemGrid);
	ItemGrid->ClearChildren();
	SlotWidgets.Empty();
	
	EFCHECK(nullptr != InventoryComponent);
	const auto InventorySlots = InventoryComponent->GetSlots();
	
	EFCHECK(nullptr != SlotWidgetClass);
	for (int32 i=0; i<InventorySlots.Num(); i++)
	{
		UEFInventorySlotWidget* NewSlot = CreateWidget<UEFInventorySlotWidget>(this, SlotWidgetClass);
		if (NewSlot)
		{
			NewSlot->SetupSlot(InventoryComponent, i);
			NewSlot->UpdateSlot(InventorySlots[i]);
			
			SlotWidgets.Add(NewSlot);
			
			// 3. 그리드에 배치 (행, 열 계산)
			int32 Row = i / SlotsPerRow;
			int32 Column = i % SlotsPerRow;

			UUniformGridSlot* NewGridSlot = ItemGrid->AddChildToUniformGrid(NewSlot, Row, Column);
			
			if (NewGridSlot)
			{
				NewGridSlot->SetHorizontalAlignment(HAlign_Center);
				NewGridSlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
	
	SourceInventoryComponent = InventoryComponent;
	
	SourceInventoryComponent->OnItemChanged.AddUObject(this, &UEFInventoryWindowWidget::RefreshSlot);
}

void UEFInventoryWindowWidget::RefreshSlot(int32 SlotIndex, const FEFItemStack& ItemStack)
{
	if (SlotWidgets.IsValidIndex(SlotIndex))
	{
		SlotWidgets[SlotIndex]->UpdateSlot(ItemStack);
	}
}

void UEFInventoryWindowWidget::DetachInventory()
{
	if (SourceInventoryComponent && InventoryUpdateHandle.IsValid())
	{
		SourceInventoryComponent->OnItemChanged.Remove(InventoryUpdateHandle);
		InventoryUpdateHandle.Reset();
	}
	SourceInventoryComponent = nullptr;
}
