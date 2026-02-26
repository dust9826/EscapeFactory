// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineMenuWidget.h"

#include "EFInventoryComponent.h"
#include "EFInventoryWindowWidget.h"
#include "EFMachineBase.h"
#include "EFRecipeDataAsset.h"
#include "EFRecipeSelectWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UEFMachineMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	RecipeSelectButton->OnClicked.AddDynamic(this, &UEFMachineMenuWidget::SwitchToRecipeList);
}

void UEFMachineMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (ProductionProgressBar && SourceMachineBase)
	{
		switch (SourceMachineBase->GetMachineState())
		{
		case EEFMachineState::SelectingRecipe:
			break;
		case EEFMachineState::Idle:
			{
				ProductionProgressBar->SetPercent(0.0f);
				break;
			}
		case EEFMachineState::Working:
			{
				float CurrentTime = SourceMachineBase->GetCurrentProgress();
				float TotalTime = SourceMachineBase->GetCurrentRecipe()->ProductionTime;

				// 2. 퍼센트 계산 (0.0 ~ 1.0 사이 값으로 클램핑)
				float ProgressPercent = (TotalTime > 0.0f) ? FMath::Clamp(CurrentTime / TotalTime, 0.0f, 1.0f) : 0.0f;
				
				ProductionProgressBar->SetPercent(ProgressPercent);
				int32 PercentInt = FMath::RoundToInt(ProgressPercent * 100.0f);
				ProgressText->SetText(FText::Format(INVTEXT("{0}%"), FText::AsNumber(PercentInt)));
				break;
			}
		case EEFMachineState::Paused:
			{
				ProgressText->SetText(FText::FromString("Production Stop"));
			}
		}
	}
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
