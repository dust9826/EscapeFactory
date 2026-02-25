// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineMenuWidget.h"

#include "EFInventoryWindowWidget.h"
#include "EFMachineBase.h"
#include "Components/WidgetSwitcher.h"

void UEFMachineMenuWidget::ConnectInventorys(UEFInventoryComponent* PlayerInven, AEFMachineBase* MachineBase)
{
	PlayerInventoryWidget->ConnectInventory(PlayerInven);
	MachineInputInventoryWidget->ConnectInventory(MachineBase->GetInputInventoryComponent());
	MachineOutputInventoryWidget->ConnectInventory(MachineBase->GetInputInventoryComponent());

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
}

void UEFMachineMenuWidget::DetachInventorys()
{
	PlayerInventoryWidget->DetachInventory();
	MachineInputInventoryWidget->DetachInventory();
	MachineOutputInventoryWidget->DetachInventory();
}

void UEFMachineMenuWidget::SwitchToRecipeList()
{
	MenuSwitcherWidget->SetActiveWidgetIndex(0);
}

void UEFMachineMenuWidget::SwitchToProduction()
{
	MenuSwitcherWidget->SetActiveWidgetIndex(1);
}
