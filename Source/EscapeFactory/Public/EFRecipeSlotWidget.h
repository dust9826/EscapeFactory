// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFRecipeSlotWidget.generated.h"

class UEFRecipeDataAsset;
class AEFMachineBase;
/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFRecipeSlotWidget : public UUserWidget
{
	GENERATED_BODY()
		
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;	
	
public:
	
	void SetupSlot(AEFMachineBase* MachineBase, int32 Index);
	
	void UpdateSlot(UEFRecipeDataAsset* NewRecipe);
	
	UEFRecipeDataAsset* GetRecipeDataAsset();

public:
	
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StackCountText;
	
private:
	UPROPERTY()
	AEFMachineBase* SourceMachine;
	
	UPROPERTY()
	int32 SlotIndex;
	
public:
	AEFMachineBase* GetSourceMachine() const { return SourceMachine; }
	int32 GetSlotIndex() const { return SlotIndex; }
};
