// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventoryComponent.h"

#include "EFItemDataAsset.h"
#include "EFRecipeDataAsset.h"

// Sets default values for this component's properties
UEFInventoryComponent::UEFInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEFInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Slots.SetNum(MaxSlots);
	if (bIsLocked)
	{
		for (FEFItemStack& Slot : Slots)
		{
			Slot.bIsLocked = true;
		}
	}
}

int32 UEFInventoryComponent::AddItem(FEFItemInstance& Item, int32 Amount)
{
	EFCHECK(nullptr != Item.ItemData || Amount <= 0, Amount);
	
	// 기존 스택에 추가 시도
	for (FEFItemStack& Slot : Slots)
	{
		if (Slot.CanStackWith(Item))
		{
			int32 Addable = Item.ItemData->MaxStackSize - Slot.Quantity;
			int32 ToAdd = FMath::Min(Addable, Amount);
			
			Slot.Quantity += ToAdd;
			Amount -= ToAdd;
			
			if (Amount <= 0)
			{
				return 0;
			}
		}
	}
	
	// 빈 슬롯에 추가 시도
	for (FEFItemStack& Slot : Slots)
	{
		if (Slot.IsEmpty() && !Slot.bIsLocked)
		{
			Slot.Item.ItemData = Item.ItemData;
			int32 ToAdd = FMath::Min(Item.ItemData->MaxStackSize, Amount);
			
			Slot.Quantity += ToAdd;
			Amount -= ToAdd;
			
			if (Amount <= 0)
			{
				return 0;
			}
		}
	}
	
	return Amount;
}

void UEFInventoryComponent::AddItem(FEFItemStack& Item)
{
	int32 ret = AddItem(Item.Item, Item.Quantity);
	Item.Quantity = ret;
}

void UEFInventoryComponent::AddItem(FEFItemStack& Item, int32 SlotIndex)
{
	FEFItemStack& Slot = Slots[SlotIndex];

	if (Slot.CanStackWith(Item))
	{
		int32 Addable = Item.Item.ItemData->MaxStackSize - Slot.Quantity;
		int32 ToAdd = FMath::Min(Addable, Item.Quantity);
			
		Slot.Quantity += ToAdd;
		Item.Quantity -= ToAdd;
	}
	else if (Slot.IsEmpty() && !Slot.bIsLocked)
	{
		Slot.Item.ItemData = Item.Item.ItemData;
		int32 ToAdd = FMath::Min(Item.Item.ItemData->MaxStackSize, Item.Quantity);
			
		Slot.Quantity += ToAdd;
		Item.Quantity -= ToAdd;
	}
}

bool UEFInventoryComponent::RemoveItem(FEFItemInstance& Item, int32 Amount)
{
	EFCHECK(HasEnoughItem(Item, Amount), false);

	for (FEFItemStack& Slot : Slots)
	{
		if (Slot.CanStackWith(Item))
		{
			int32 ToRemove = FMath::Min(Amount, Slot.Quantity);
			Slot.Quantity -= ToRemove;
			Amount -= ToRemove;

			if (Slot.Quantity <= 0 && !Slot.bIsLocked)
			{
				Slot.Item.ItemData = nullptr;
			}
			if (Amount <= 0) 
			{
				return true;
			}
		}
	}
	return false;
}

bool UEFInventoryComponent::HasEnoughItem(FEFItemInstance& Item, int32 Amount)
{
	int32 TotalFound = 0;
	for (const FEFItemStack& Slot : Slots)
	{
		if (Slot.CanStackWith(Item))
		{
			TotalFound += Slot.Quantity;
		}
	}
	return TotalFound >= Amount;
}

void UEFInventoryComponent::SetupRecipe(TArray<FEFItemCount> ItemCounts)
{
	int recipeSize = ItemCounts.Num();

	EFCHECK(recipeSize <= MaxSlots);
	for (int i = 0; i < recipeSize; i++)
	{
		Slots[i].Item.ItemData = ItemCounts[i].ItemData;
		Slots[i].Quantity = 0;
		Slots[i].bIsLocked = true;
	}
	
	for (int i = recipeSize; i < MaxSlots; i++)
	{
		Slots[i].Item.ItemData = nullptr;
		Slots[i].Quantity = 0;
		Slots[i].bIsLocked = true;
	}
	
	EFLOG(Warning, TEXT("This Function Force Slots Quantity to Zero. Check Later"));
}

TArray<FEFItemStack>& UEFInventoryComponent::GetSlots() 
{
	return Slots;
}

void UEFInventoryComponent::SetMaxSlots(int32 Size)
{
	MaxSlots = Size;
}


