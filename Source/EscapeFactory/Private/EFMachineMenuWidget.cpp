// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineMenuWidget.h"

#include "EFInventoryComponent.h"
#include "EFInventoryWindowWidget.h"
#include "EFMachineBase.h"
#include "EFRecipeSelectWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UEFMachineMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	RecipeSelectButton->OnClicked.AddDynamic(this, &UEFMachineMenuWidget::SwitchToRecipeList);
}

void UEFMachineMenuWidget::ConnectInventorys(UEFInventoryComponent* PlayerInven, AEFMachineBase* MachineBase)
{
	// Recipe Select
	SourceMachineBase = MachineBase;
	
	RecipeSelectWidget->RefreshSlots(MachineBase);
	MachineRecipeHandle = SourceMachineBase->OnMachineRecipeSelected.AddUObject(this, &UEFMachineMenuWidget::SwitchToProduction);
	
	switch (MachineBase->GetMachineState())
	{
	case EEFMachineState::SelectingRecipe:
		{
			SwitchToRecipeList();
			break;
		}
	default:
		{
			SwitchToProduction();
			break;
		}
	}
	
	// Production
	PlayerInventoryWidget->ConnectInventory(PlayerInven);
	MachineInputInventoryWidget->ConnectInventory(MachineBase->GetInputInventoryComponent());
	MachineOutputInventoryWidget->ConnectInventory(MachineBase->GetOutputInventoryComponent());
}

void UEFMachineMenuWidget::DetachInventorys()
{
	PlayerInventoryWidget->DetachInventory();
	MachineInputInventoryWidget->DetachInventory();
	MachineOutputInventoryWidget->DetachInventory();

	if (SourceMachineBase)
	{
		SourceMachineBase->OnMachineRecipeSelected.Remove(MachineRecipeHandle);
	}
	
	SourceMachineBase = nullptr;
	
}

void UEFMachineMenuWidget::SwitchToRecipeList()
{
	MenuSwitcherWidget->SetActiveWidgetIndex(0);
	EFCHECK(nullptr != SourceMachineBase);
	SourceMachineBase->SetMachineState(EEFMachineState::SelectingRecipe);
	SourceMachineBase->GetInputInventoryComponent()->DropRecipe();
}

void UEFMachineMenuWidget::SwitchToProduction()
{
	MenuSwitcherWidget->SetActiveWidgetIndex(1);
}
