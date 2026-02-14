// Fill out your copyright notice in the Description page of Project Settings.


#include "EFPlayerController.h"

#include "EFCharacter.h"
#include "EFInventoryWindowWidget.h"
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

void AEFPlayerController::ToggleInventory()
{
	if (!bInventoryOpen)
    {
        // 1. 위젯 생성 및 뷰포트 추가
        if (!InventoryUI && InventoryWidgetClass)
        {
            InventoryUI = CreateWidget<UEFInventoryWindowWidget>(this, InventoryWidgetClass);
        }

        if (InventoryUI)
        {
            InventoryUI->AddToViewport();

            // 2. 캐릭터의 인벤토리 데이터 주입 (캐릭터를 가져와서 컴포넌트 전달)
            if (AEFCharacter* EFChar = Cast<AEFCharacter>(GetPawn()))
            {
                InventoryUI->RefreshInventory(EFChar->GetInventoryComponent());
            }

            // 3. 마우스 커서 활성화 및 입력 모드 전환
            SetShowMouseCursor(true);
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(InventoryUI->TakeWidget());
            SetInputMode(InputMode);
            
            bInventoryOpen = true;
        }
    }
    else
    {
        // 4. UI 닫기 및 입력 모드 복구
        if (InventoryUI)
        {
            InventoryUI->RemoveFromParent();
        }

        SetShowMouseCursor(false);
        SetInputMode(FInputModeGameOnly());
        
        bInventoryOpen = false;
    }
}
