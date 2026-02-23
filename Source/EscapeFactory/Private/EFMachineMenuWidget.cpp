// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineMenuWidget.h"

#include "EFInventoryWindowWidget.h"

void UEFMachineMenuWidget::ConnectInventorys(UEFInventoryComponent* PlayerInven, UEFInventoryComponent* InputInven,
	UEFInventoryComponent* OutputInven)
{
	PlayerInventoryWidget->ConnectInventory(PlayerInven);
	MachineInputInventoryWidget->ConnectInventory(InputInven);
	MachineOutputInventoryWidget->ConnectInventory(OutputInven);
}

void UEFMachineMenuWidget::DetachInventorys()
{
	PlayerInventoryWidget->DetachInventory();
	MachineInputInventoryWidget->DetachInventory();
	MachineOutputInventoryWidget->DetachInventory();
}
