// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "Components/ActorComponent.h"
#include "EFInventoryComponent.generated.h"

class UEFRecipeDataAsset;
struct FEFItemInstance;
struct FEFItemStack;
struct FEFItemCount;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, int32, const FEFItemStack&);

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
	int32 AddItem(FEFItemInstance& Item, int32 Amount);
	void AddItem(FEFItemStack& Item);
	void AddItem(FEFItemStack& Item, int32 SlotIndex);
	
	bool RemoveItem(FEFItemInstance& Item, int32 Amount);
	
	bool HasEnoughItem(FEFItemInstance& Item, int32 Amount);
	
	void ChangeItem(FEFItemStack& Item, int32 SlotIndex);
	
public:
	// Machine 레시피 고정에 필요. 상속으로 빼도 될듯.
	void SetupRecipe(TArray<FEFItemCount> ItemCounts);
	
	TArray<FEFItemStack>& GetSlots();
	
	void SetMaxSlots(int32 Size);
	
public:
	FOnInventoryItemChanged OnItemChanged;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxSlots = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FEFItemStack> Slots;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bIsLocked = false;
};
