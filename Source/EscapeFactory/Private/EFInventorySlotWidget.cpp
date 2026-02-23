// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventorySlotWidget.h"

#include "EFInventoryComponent.h"
#include "EFInventoryDragDropOp.h"
#include "EFItemDataAsset.h"
#include "EFItemVisualWidget.h"
#include "EFPlayerController.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


FReply UEFInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Ctrl + LeftMouse
	if (!bIsEmpty && InMouseEvent.IsControlDown() && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer()))
		{
			PC->HandleQuickMove(SourceInventory, SlotIndex);
			return FReply::Handled();
		}
	}
	// LeftMouse
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer());
        
		// [Case 1 - 변형] 이미 선택된 슬롯이 있는 경우 -> Swap 시도
		if (PC && PC->GetSelectedSlot())
		{
			if (PC->GetSelectedSlot() != this)
			{
				PC->SwapSlot(PC->GetSelectedSlot(), this);
			}
			PC->SetSelectedSlot(nullptr); // 스왑 후 선택 해제
			
			if (PC && PC->ItemVisualWidget)
			{
				PC->ItemVisualWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
			return FReply::Handled();
		}
		
		if (bIsEmpty)
			return FReply::Unhandled();

		// [Case 1] 처음 클릭 시 -> 이 슬롯을 선택 상태로 후보 등록
		if (PC) PC->SetSelectedSlot(this);

		if (PC && PC->ItemVisualWidget)
		{
			PC->ItemVisualWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			PC->ItemVisualWidget->UpdateVisual(ItemIcon, StackCountText->GetText());
		}
		
		// [Case 2] 드래그 감지 예약
		// 마우스를 떼지 않고 움직이면 NativeOnDragDetected로 넘어감
		return FReply::Unhandled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	
	return FReply::Unhandled();
}

void UEFInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                  UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	UEFInventoryDragDropOp* DragOp = NewObject<UEFInventoryDragDropOp>();DragOp->SourceSlotWidget = this;
	
	AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer());
        
	if (PC && PC->GetSelectedSlot())
	{
		PC->SetSelectedSlot(nullptr);
	}
	
	OutOperation = DragOp; 
}

bool UEFInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer());
		
	if (PC && PC->ItemVisualWidget)
	{
		PC->ItemVisualWidget->SetVisibility(ESlateVisibility::Collapsed);
		EFLOG_S(Warning);
	}
	
	if (UEFInventoryDragDropOp* DragOp = Cast<UEFInventoryDragDropOp>(InOperation))
	{
		if (PC)
		{
			PC->MoveSlot(DragOp->SourceSlotWidget, this);
			return true; 
		}
	}
	
	return false;
}

void UEFInventorySlotWidget::SetupSlot(UEFInventoryComponent* SourceInv, int32 Index)
{
	SourceInventory = SourceInv;
	SlotIndex = Index;
}

void UEFInventorySlotWidget::UpdateSlot(const FEFItemStack& NewStack)
{
	if (NewStack.Item.ItemData == nullptr)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		StackCountText->SetVisibility(ESlateVisibility::Hidden);
		bIsEmpty = true;
		return;
	}
	
	if (ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(NewStack.Item.ItemData->Icon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}

	if (StackCountText)
	{
		StackCountText->SetText(FText::AsNumber(NewStack.Quantity));
		StackCountText->SetVisibility(ESlateVisibility::Visible);
	}
	
	bIsEmpty = false;
}

FEFItemStack& UEFInventorySlotWidget::GetItemStack()
{
	return SourceInventory->GetSlots()[SlotIndex];
}
