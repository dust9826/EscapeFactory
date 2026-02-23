// Fill out your copyright notice in the Description page of Project Settings.


#include "EFItemVisualWidget.h"

#include "EFPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UEFItemVisualWidget::UpdateVisual(UImage* Icon, FText Text)
{
	if (ItemIcon)
	{
		ItemIcon->SetBrush(Icon->GetBrush());
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
	}

	if (StackCountText)
	{
		StackCountText->SetText(Text);
		StackCountText->SetVisibility(ESlateVisibility::Visible);
	}
	
	if (!IsInViewport())
	{
		AddToViewport(999); 
	}
	SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
}

void UEFItemVisualWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// 1. 현재 선택된 슬롯이 있는지 확인 (PC에서 가져옴)
	AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer());
	
	if (PC)
	{
		FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		
		float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
		FVector2D CorrectedPos = MousePosition * ViewportScale;
		
		EFLOG(Warning, TEXT("%f"), MousePosition.X);
		EFLOG(Warning, TEXT("%f"), ViewportScale);
		
		SetPositionInViewport(CorrectedPos);
	}
}
