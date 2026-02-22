// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineMenuWidget.h"

#include "EFInventoryWindowWidget.h"

void UEFMachineMenuWidget::RefreshInventorys(const UEFInventoryComponent* PlayerInven, const UEFInventoryComponent* InputInven,
	const UEFInventoryComponent* OutputInven)
{
	PlayerInventoryWidget->RefreshInventory(PlayerInven);
	MachineInputInventoryWidget->RefreshInventory(InputInven);
	MachineOutputInventoryWidget->RefreshInventory(OutputInven);
}
