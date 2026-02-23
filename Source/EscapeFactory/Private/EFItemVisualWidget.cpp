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
	
	UpdatePosition();
}

void UEFItemVisualWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdatePosition();
}

void UEFItemVisualWidget::UpdatePosition()
{
	AEFPlayerController* PC = Cast<AEFPlayerController>(GetOwningPlayer());
	
	if (PC)
	{
		FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		
		float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
		FVector2D CorrectedPos = MousePosition * ViewportScale;
		
		SetPositionInViewport(CorrectedPos);
	}
}
