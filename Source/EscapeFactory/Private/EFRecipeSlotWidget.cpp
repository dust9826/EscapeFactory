// Fill out your copyright notice in the Description page of Project Settings.


#include "EFRecipeSlotWidget.h"

#include "EFMachineBase.h"
#include "EFRecipeDataAsset.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

FReply UEFRecipeSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (SourceMachine)
		{
			SourceMachine->SelectRecipe(GetRecipeDataAsset());
			SourceMachine->OnMachineRecipeSelected.Broadcast();
		}
		
		return FReply::Handled();
	}
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UEFRecipeSlotWidget::SetupSlot(AEFMachineBase* MachineBase, int32 Index)
{
	SourceMachine = MachineBase;
	SlotIndex = Index;
}

void UEFRecipeSlotWidget::UpdateSlot(UEFRecipeDataAsset* NewRecipe)
{
	if (NewRecipe == nullptr)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		StackCountText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	
	if (ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(NewRecipe->Icon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}

	if (StackCountText)
	{
		StackCountText->SetText(FText::AsNumber(NewRecipe->ProductionTime));
		StackCountText->SetVisibility(ESlateVisibility::Visible);
	}
}

UEFRecipeDataAsset* UEFRecipeSlotWidget::GetRecipeDataAsset()
{
	return SourceMachine->GetAvailableRecipes()[SlotIndex];
}
