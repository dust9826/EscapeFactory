// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFItemVisualWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFItemVisualWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateVisual(class UImage* Icon, FText Text);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void UpdatePosition();
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StackCountText;
	
};
