// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventorySlotWidget.h"

#include "EFItemDataAsset.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UEFInventorySlotWidget::UpdateSlot(const FEFItemStack& NewStack)
{
	if (NewStack.Item.ItemData == nullptr)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		StackCountText->SetVisibility(ESlateVisibility::Hidden);
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
}
