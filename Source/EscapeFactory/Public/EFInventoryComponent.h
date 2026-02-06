// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "Components/ActorComponent.h"
#include "EFInventoryComponent.generated.h"

struct FEFItemInstance;
struct FEFItemStack;

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
	int32 AddItem(FEFItemInstance& Item, int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FEFItemInstance& Item, int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasEnoughItem(FEFItemInstance& Item, int32 Amount);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxSlots = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FEFItemStack> Slots;
		
	
};
