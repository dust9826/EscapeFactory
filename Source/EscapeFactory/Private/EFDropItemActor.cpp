// Fill out your copyright notice in the Description page of Project Settings.


#include "EFDropItemActor.h"

#include "EFCharacter.h"
#include "EFInventoryComponent.h"

// Sets default values
AEFDropItemActor::AEFDropItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	static ConstructorHelpers::FObjectFinder<UEFItemDataAsset> 
		ItemDataAsset(TEXT("/Game/EscapeFactory/DataAssets/Item/DA_Item_Scrap.DA_Item_Scrap"));
	if (ItemDataAsset.Succeeded())
	{
		FEFItemInstance Item;
		Item.ItemData = ItemDataAsset.Object;
		ItemStack.Item = Item;
		ItemStack.Quantity = 50;
	}
}

// Called when the game starts or when spawned
void AEFDropItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEFDropItemActor::Interact(AActor* Interactor)
{
	EFCHECK(nullptr != Interactor);
	
	AEFCharacter* EFCharacter = Cast<AEFCharacter>(Interactor);
	EFCHECK(nullptr != EFCharacter);
	
	UEFInventoryComponent* PlayerInv = EFCharacter->GetInventoryComponent();
	EFCHECK(nullptr != PlayerInv);
    
	int32 remain = PlayerInv->AddItem(ItemStack.Item, ItemStack.Quantity);
	ItemStack.Quantity = remain;
	if (remain <= 0)
	{
		Destroy();
	}
}

void AEFDropItemActor::InitializeDrop(const FEFItemStack& InStack)
{
	ItemStack = InStack;
	
	if (ItemStack.Item.ItemData)
	{
		// Mesh 적용
	}
}

