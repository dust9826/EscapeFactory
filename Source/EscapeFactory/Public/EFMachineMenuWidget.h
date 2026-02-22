// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFMachineMenuWidget.generated.h"

class UEFInventoryWindowWidget;
class UEFInventoryComponent;

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFMachineMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* PlayerInventoryWidget;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* MachineInputInventoryWidget;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* MachineOutputInventoryWidget;
	
public:
	void RefreshInventorys(const UEFInventoryComponent* PlayerInven,
		const UEFInventoryComponent* InputInven, const UEFInventoryComponent* OutputInven);
};
