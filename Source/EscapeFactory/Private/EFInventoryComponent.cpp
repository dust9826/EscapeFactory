// Fill out your copyright notice in the Description page of Project Settings.


#include "EFInventoryComponent.h"

#include "EFDropItemActor.h"
#include "EFItemDataAsset.h"
#include "EFRecipeDataAsset.h"

// Sets default values for this component's properties
UEFInventoryComponent::UEFInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FClassFinder<AEFDropItemActor>
		BP_DROPITEM(TEXT("/Game/EscapeFactory/Blueprints/BP_DropItem.BP_DropItem_C"));
	
	if (BP_DROPITEM.Succeeded())
	{
		DropItemClass = BP_DROPITEM.Class;
	}
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
	for (int i=0; i<Slots.Num(); i++)
	{
		FEFItemStack& Slot = Slots[i];
		if (Slot.CanStackWith(Item))
		{
			int32 Addable = Item.ItemData->MaxStackSize - Slot.Quantity;
			int32 ToAdd = FMath::Min(Addable, Amount);
			
			Slot.Quantity += ToAdd;
			Amount -= ToAdd;
			
			OnItemChanged.Broadcast(i, Slot);
			
			if (Amount <= 0)
			{
				return 0;
			}
		}
	}
	
	// 빈 슬롯에 추가 시도
	for (int i=0; i<Slots.Num(); i++)
	{
		FEFItemStack& Slot = Slots[i];
		if (Slot.IsEmpty() && !Slot.bIsLocked)
		{
			Slot.Item.ItemData = Item.ItemData;
			int32 ToAdd = FMath::Min(Item.ItemData->MaxStackSize, Amount);
			
			Slot.Quantity += ToAdd;
			Amount -= ToAdd;
			
			OnItemChanged.Broadcast(i, Slot);
			
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
	
	if (Item.Quantity <= 0 && !Item.bIsLocked)
	{
		Item.Item.ItemData = nullptr;
	}
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
	
	if (Item.Quantity <= 0 && !Item.bIsLocked)
	{
		Item.Item.ItemData = nullptr;
	}
	
	OnItemChanged.Broadcast(SlotIndex, Slot);
}

bool UEFInventoryComponent::RemoveItem(FEFItemInstance& Item, int32 Amount)
{
	EFCHECK(HasEnoughItem(Item, Amount), false);

	for (int i=0; i<Slots.Num(); i++)
	{
		FEFItemStack& Slot = Slots[i];
		if (Slot.CanStackWith(Item))
		{
			int32 ToRemove = FMath::Min(Amount, Slot.Quantity);
			Slot.Quantity -= ToRemove;
			Amount -= ToRemove;

			if (Slot.Quantity <= 0 && !Slot.bIsLocked)
			{
				Slot.Item.ItemData = nullptr;
			}
			
			OnItemChanged.Broadcast(i, Slot);
			
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

void UEFInventoryComponent::ChangeItem(FEFItemStack& Item, int32 SlotIndex)
{
	Slots[SlotIndex].Item.ItemData = Item.Item.ItemData;
	Slots[SlotIndex].Quantity = Item.Quantity;
	Slots[SlotIndex].bIsLocked = Item.bIsLocked;
	OnItemChanged.Broadcast(SlotIndex, Slots[SlotIndex]);
}

void UEFInventoryComponent::DropItem(int32 SlotIndex)
{
	if (Slots[SlotIndex].IsEmpty())
		return;
	
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	// 1. 월드 및 클래스 유효성 검사
	EFCHECK(World != nullptr);
	EFCHECK(DropItemClass != nullptr);

	// 2. 스폰 위치 및 회전 설정 (보통 플레이어 앞쪽)
	FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 300.0f;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// 3. 스폰 설정 (충돌 처리 등)
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;
	SpawnParams.Instigator = Cast<APawn>(GetOwner());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 4. 액터 스폰
	AEFDropItemActor* DroppedActor = World->SpawnActor<AEFDropItemActor>(DropItemClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (DroppedActor)
	{
		// 5. 스폰된 액터에 아이템 데이터 주입
		DroppedActor->InitializeDrop(Slots[SlotIndex]);
	}
	
	Slots[SlotIndex].Quantity = 0;
	if (!Slots[SlotIndex].bIsLocked)
	{
		Slots[SlotIndex].Item.ItemData = nullptr;
	}
	OnItemChanged.Broadcast(SlotIndex, Slots[SlotIndex]);
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
		OnItemChanged.Broadcast(i, Slots[i]);
	}
	
	for (int i = recipeSize; i < MaxSlots; i++)
	{
		Slots[i].Item.ItemData = nullptr;
		Slots[i].Quantity = 0;
		Slots[i].bIsLocked = true;
		OnItemChanged.Broadcast(i, Slots[i]);
	}
	
	EFLOG(Warning, TEXT("This Function Force Slots Quantity to Zero. Check Later"));
}

void UEFInventoryComponent::DropRecipe()
{
	for (int i = 0; i < MaxSlots; i++)
	{
		DropItem(i);
	}
}

TArray<FEFItemStack>& UEFInventoryComponent::GetSlots() 
{
	return Slots;
}

void UEFInventoryComponent::SetMaxSlots(int32 Size)
{
	MaxSlots = Size;
}


