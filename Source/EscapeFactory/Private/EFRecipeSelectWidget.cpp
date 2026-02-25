// Fill out your copyright notice in the Description page of Project Settings.


#include "EFRecipeSelectWidget.h"

#include "EFMachineBase.h"

void UEFRecipeSelectWidget::RefreshSlots(AEFMachineBase* MachineBase)
{
	MachineBaseSource = MachineBase;
	TArray<UEFRecipeDataAsset*> Recipes = MachineBase->GetAvailableRecipes();
}
