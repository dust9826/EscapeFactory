// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "GameFramework/PlayerController.h"
#include "EFPlayerController.generated.h"

class UEFMachineMenuWidget;
class AEFMachineBase;
class UEFInteractionWidget;
class UEFPlayerMenuWidget;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EEFUIState : uint8
{
	None,           // 기본 상태 (Crosshair만 표시)
	Inventory,      // 플레이어 가방만 열림
	MachineMenu,    // 기계 조작 중 (기계 인벤토리 + 플레이어 가방)
	Dialogue        // NPC 대화 등 (나중에 확장용)
};

/**
 * 
 */
UCLASS(abstract, config="Game")
class ESCAPEFACTORY_API AEFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AEFPlayerController();

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
public:
	
	void ChangeUIState(EEFUIState NewState);
	
	void UpdateInteractionName(FString NewName);
	
	void UpdatePlayerInventory();
	
	void UpdateMachineMenu(AEFMachineBase* MachineBase);
	
public:
	
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UEFPlayerMenuWidget> PlayerMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="UI")
	UEFPlayerMenuWidget* PlayerMenuWidget;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UEFInteractionWidget> InteractionWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="UI")
	UEFInteractionWidget* InteractionWidget;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UEFMachineMenuWidget> MachineMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="UI")
	UEFMachineMenuWidget* MachineMenuWidget;
	
private:
	EEFUIState CurrentUIState = EEFUIState::None;
};
