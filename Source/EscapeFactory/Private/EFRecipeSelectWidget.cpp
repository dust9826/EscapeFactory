// Fill out your copyright notice in the Description page of Project Settings.


#include "EFRecipeSelectWidget.h"

#include "EFMachineBase.h"
#include "EFRecipeSlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

class UEFRecipeSlotWidget;

void UEFRecipeSelectWidget::RefreshSlots(AEFMachineBase* MachineBase)
{
	EFCHECK(nullptr != RecipeGrid);
	RecipeGrid->ClearChildren();
	SlotWidgets.Empty();
	
	EFCHECK(nullptr != MachineBase);
	MachineBaseSource = MachineBase;
	TArray<UEFRecipeDataAsset*> Recipes = MachineBase->GetAvailableRecipes();
	EFLOG(Warning, TEXT("Available Recipes : %d"), Recipes.Num());
	EFCHECK(nullptr != SlotWidgetClass);
	for (int32 i=0; i<Recipes.Num(); i++)
	{
		UEFRecipeSlotWidget* NewSlot = CreateWidget<UEFRecipeSlotWidget>(this, SlotWidgetClass);
		if (NewSlot)
		{
			NewSlot->SetupSlot(MachineBase, i);
			NewSlot->UpdateSlot(Recipes[i]);
			
			SlotWidgets.Add(NewSlot);
			
			// 3. 그리드에 배치 (행, 열 계산)
			int32 Row = i / SlotsPerRow;
			int32 Column = i % SlotsPerRow;

			UUniformGridSlot* NewGridSlot = RecipeGrid->AddChildToUniformGrid(NewSlot, Row, Column);
			
			if (NewGridSlot)
			{
				NewGridSlot->SetHorizontalAlignment(HAlign_Center);
				NewGridSlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
}
