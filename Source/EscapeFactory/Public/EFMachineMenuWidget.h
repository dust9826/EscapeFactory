// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFMachineMenuWidget.generated.h"

class UEFRecipeSelectWidget;
class UButton;
class UProgressBar;
class UTextBlock;
class UEFInventoryWindowWidget;
class UEFInventoryComponent;
class UWidgetSwitcher;
class AEFMachineBase;

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFMachineMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFRecipeSelectWidget* RecipeSelectWidget;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* PlayerInventoryWidget;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* MachineInputInventoryWidget;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UEFInventoryWindowWidget* MachineOutputInventoryWidget;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProductionProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ProgressText;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* RecipeSelectButton;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"))
	UWidgetSwitcher* MenuSwitcherWidget;
	
	
public:
	void ConnectInventorys(UEFInventoryComponent* PlayerInven, AEFMachineBase* MachineBase);
	void DetachInventorys();
	
	UFUNCTION()
	void SwitchToRecipeList();
	
	UFUNCTION()
	void SwitchToProduction();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Machine")
	AEFMachineBase* SourceMachineBase;
	
	FDelegateHandle MachineRecipeHandle;
};
