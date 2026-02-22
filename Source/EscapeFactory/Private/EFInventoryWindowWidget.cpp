// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventoryWindowWidget.h"

#include "EFInventoryComponent.h"
#include "EFInventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UEFInventoryWindowWidget::RefreshInventory(const UEFInventoryComponent* InventoryComponent)
{
	EFCHECK(nullptr != ItemGrid);
	ItemGrid->ClearChildren();
	
	EFCHECK(nullptr != InventoryComponent);
	const auto InventorySlots = InventoryComponent->GetSlots();
	
	EFCHECK(nullptr != SlotWidgetClass);
	for (int32 i=0; i<InventorySlots.Num(); i++)
	{
		UEFInventorySlotWidget* NewSlot = CreateWidget<UEFInventorySlotWidget>(this, SlotWidgetClass);
		if (NewSlot)
		{
			// 데이터 주입 (아까 만든 UpdateSlot 호출)
			NewSlot->UpdateSlot(InventorySlots[i]);

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
}
