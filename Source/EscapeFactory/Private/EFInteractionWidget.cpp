// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInteractionWidget.h"

#include "Components/TextBlock.h"

void UEFInteractionWidget::SetInteractionName(FString NewName)
{
	if (InteractionText)
	{
		InteractionText->SetText(FText::FromString(NewName));
	}
}
