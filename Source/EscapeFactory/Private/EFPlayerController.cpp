// Fill out your copyright notice in the Description page of Project Settings.


#include "EFPlayerController.h"

#include "EFCharacter.h"
#include "EFInteractionWidget.h"
#include "EFInventoryComponent.h"
#include "EFInventorySlotWidget.h"
#include "EFInventoryWindowWidget.h"
#include "EFItemDataAsset.h"
#include "EFItemVisualWidget.h"
#include "EFMachineBase.h"
#include "EFMachineMenuWidget.h"
#include "EFPlayerMenuWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EscapeFactoryCameraManager.h"

AEFPlayerController::AEFPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AEscapeFactoryCameraManager::StaticClass();
}

void AEFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	EFCHECK(nullptr != InteractionWidgetClass);
	InteractionWidget = CreateWidget<UEFInteractionWidget>(this, InteractionWidgetClass);
	EFCHECK(nullptr != InteractionWidget);
	InteractionWidget->AddToViewport();
	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	EFCHECK(nullptr != PlayerMenuWidgetClass);
	PlayerMenuWidget = CreateWidget<UEFPlayerMenuWidget>(this, PlayerMenuWidgetClass);
	EFCHECK(nullptr != PlayerMenuWidget);
	PlayerMenuWidget->AddToViewport();
	PlayerMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	EFCHECK(nullptr != MachineMenuWidgetClass);
	MachineMenuWidget = CreateWidget<UEFMachineMenuWidget>(this, MachineMenuWidgetClass);
	EFCHECK(nullptr != MachineMenuWidget);
	MachineMenuWidget->AddToViewport();
	MachineMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	EFCHECK(nullptr != ItemVisualWidgetClass);
	ItemVisualWidget = CreateWidget<UEFItemVisualWidget>(this, ItemVisualWidgetClass);
	EFCHECK(nullptr != ItemVisualWidget);
	ItemVisualWidget->AddToViewport();
	ItemVisualWidget->SetVisibility(ESlateVisibility::Hidden);
	
	ChangeUIState(EEFUIState::None);
}

void AEFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}

void AEFPlayerController::ChangeUIState(EEFUIState NewState)
{
	EFCHECK(nullptr != InteractionWidget);
	EFCHECK(nullptr != PlayerMenuWidget);
	EFCHECK(nullptr != MachineMenuWidget);
	
	PlayerMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	MachineMenuWidget->SetVisibility(ESlateVisibility::Collapsed);		
	
	if (CurrentUIState == NewState)
		CurrentUIState = EEFUIState::None;
	else
		CurrentUIState = NewState;
	
	switch (CurrentUIState)
	{
	case EEFUIState::None:
		{
			SetIgnoreLookInput(false); 
			SetShowMouseCursor(false);
			SetInputMode(FInputModeGameOnly());

			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	case EEFUIState::Inventory:
		{
			SetIgnoreLookInput(true); 
			SetShowMouseCursor(true);
			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetWidgetToFocus(PlayerMenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);
			
			UpdatePlayerInventory();
			
			PlayerMenuWidget->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	case EEFUIState::MachineMenu:
		{
			SetIgnoreLookInput(true); 
			SetShowMouseCursor(true);
			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetWidgetToFocus(MachineMenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);
			
			UpdatePlayerInventory();
			
			MachineMenuWidget->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
}

void AEFPlayerController::UpdatePlayerInventory()
{
	if (PlayerMenuWidget)
	{
		if (AEFCharacter* EFChar = Cast<AEFCharacter>(GetPawn()))
		{
			PlayerMenuWidget->PlayerInventoryWidget->ConnectInventory(EFChar->GetInventoryComponent());
			CurrentInventoryComponent = EFChar->GetInventoryComponent();
		}
	}
}

void AEFPlayerController::UpdateMachineMenu(AEFMachineBase* MachineBase)
{
	if (AEFCharacter* EFChar = Cast<AEFCharacter>(GetPawn()))
	{
		MachineMenuWidget->ConnectInventorys(EFChar->GetInventoryComponent(), MachineBase);
		CurrentTargetMachine = MachineBase;
	}
}

void AEFPlayerController::HandleQuickMove(class UEFInventoryComponent* SourceInv, int32 SlotIndex)
{
	if (CurrentUIState == EEFUIState::MachineMenu)
	{
		EFCHECK(nullptr != SourceInv);
	
		UEFInventoryComponent* DestinationInv = FindDestinationInventory(SourceInv);
		EFCHECK(nullptr != DestinationInv);
	
		FEFItemStack& ItemStack = SourceInv->GetSlots()[SlotIndex];
	
		DestinationInv->AddItem(ItemStack);
		
		SourceInv->OnItemChanged.Broadcast(SlotIndex, ItemStack);
		
		UpdateMachineMenu(CurrentTargetMachine);
	}
}

void AEFPlayerController::SwapSlot(UEFInventorySlotWidget* FromSlot, UEFInventorySlotWidget* ToSlot)
{
	FEFItemStack& FromItemStack = FromSlot->GetItemStack();
	FEFItemStack& ToItemStack = ToSlot->GetItemStack();
	
	if (!FromItemStack.IsEmpty())
	{
		if (ToItemStack.CanStackWith(FromItemStack) || (ToItemStack.IsEmpty() && !ToItemStack.bIsLocked))
		{
			ToSlot->GetSourceInventory()->AddItem(FromItemStack, ToSlot->GetSlotIndex());
			FromSlot->GetSourceInventory()->OnItemChanged.Broadcast(FromSlot->GetSlotIndex(), FromItemStack);
		}
		else if (!FromItemStack.bIsLocked && !ToItemStack.bIsLocked)
		{
			EFLOG_S(Warning);
			FEFItemStack FromTemp = FromItemStack;
			FEFItemStack ToTemp = ToItemStack;
			FromSlot->GetSourceInventory()->ChangeItem(ToTemp, FromSlot->GetSlotIndex());
			ToSlot->GetSourceInventory()->ChangeItem(FromTemp, ToSlot->GetSlotIndex());
		}
	}
}

void AEFPlayerController::MoveSlot(UEFInventorySlotWidget* FromSlot, UEFInventorySlotWidget* ToSlot)
{
	FEFItemStack& FromItemStack = FromSlot->GetItemStack();
	if (!FromItemStack.IsEmpty())
	{
		ToSlot->GetSourceInventory()->AddItem(FromItemStack, ToSlot->GetSlotIndex());
		FromSlot->GetSourceInventory()->OnItemChanged.Broadcast(FromSlot->GetSlotIndex(), FromItemStack);
	}
}

UEFInventoryComponent* AEFPlayerController::FindDestinationInventory(UEFInventoryComponent* SourceInv)
{
	if (SourceInv == CurrentInventoryComponent)
	{
		return CurrentTargetMachine->GetInputInventoryComponent();
	}
	if (SourceInv == CurrentTargetMachine->GetInputInventoryComponent() ||
		SourceInv == CurrentTargetMachine->GetOutputInventoryComponent())
	{
		return CurrentInventoryComponent;
	}
	return nullptr;
}

void AEFPlayerController::UpdateInteractionName(FString NewName)
{
	InteractionWidget->SetInteractionName(NewName);
}
