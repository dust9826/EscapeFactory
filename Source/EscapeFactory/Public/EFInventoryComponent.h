// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "Components/ActorComponent.h"
#include "EFInventoryComponent.generated.h"


struct FEFItemSlot;
class UEFItemDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFACTORY_API UEFInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEFInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 AddItem(UEFItemDataAsset* Item, int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UEFItemDataAsset* Item, int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasEnoughItem(UEFItemDataAsset* Item, int32 Amount);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxSlots = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FEFItemSlot> Slots;
		
};
