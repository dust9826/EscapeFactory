// Fill out your copyright notice in the Description page of Project Settings.


#include "EFMachineBase.h"

#include "EFInventoryComponent.h"
#include "EFItemDataAsset.h"
#include "EFPlayerController.h"
#include "EFRecipeDataAsset.h"


// Sets default values
AEFMachineBase::AEFMachineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	
	InputInventory = CreateDefaultSubobject<UEFInventoryComponent>(FName("InputInventory"));
	OutputInventory = CreateDefaultSubobject<UEFInventoryComponent>(FName("OutputInventory"));
	
	InputInventory->SetMaxSlots(3);
	OutputInventory->SetMaxSlots(1);
	
	SetMachineState(EEFMachineState::SelectingRecipe);
}

// Called when the game starts or when spawned
void AEFMachineBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEFMachineBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateProduction(DeltaTime);
}

void AEFMachineBase::Interact(AActor* Interactor)
{
	EFLOG(Warning, TEXT("Machine Interacted by %s"), *Interactor->GetName());
	
	AEFPlayerController* PC = Cast<AEFPlayerController>(Interactor->GetInstigatorController());
	EFCHECK(nullptr != PC);
	
	PC->UpdateMachineMenu(this);
	PC->ChangeUIState(EEFUIState::MachineMenu);
}

FString AEFMachineBase::GetInteractName() const
{
	return MachineName.IsEmpty() ? GetClass()->GetName() : MachineName;;
}

void AEFMachineBase::UpdateProduction(float DeltaTime)
{
	switch (CurrentState)
	{
	case EEFMachineState::SelectingRecipe:
		break;
	case EEFMachineState::Idle:
		{
			if (!RemainItems.IsEmpty())
			{
				FlushRemainItems();
				break;
			}
			
			if (CanProcessRecipe())
			{
				ConsumeIngredients();
				SetMachineState(EEFMachineState::Working);
			}
			break;
		}
	case EEFMachineState::Working:
		{
			CurrentProgress += DeltaTime;
			if (CurrentProgress >= CurrentRecipe->ProductionTime)
			{
				ProduceOutput();
				CurrentProgress = 0.0f;
				SetMachineState(EEFMachineState::Idle);
			}
			break;
		}
	case EEFMachineState::Paused:
		break;
	}
}

void AEFMachineBase::SetupInventoryRecipe()
{
	EFCHECK(nullptr != CurrentRecipe);
	
	// Machine의 인벤토리를 비우는 과정 필요
	
	InputInventory->SetupRecipe(CurrentRecipe->InputItem);
}

void AEFMachineBase::SetMachineState(EEFMachineState NewState)
{
	CurrentState = NewState;
}

void AEFMachineBase::SelectRecipe(UEFRecipeDataAsset* NewRecipe)
{
	EFCHECK(nullptr != NewRecipe);
	
	CurrentRecipe = NewRecipe;
	
	SetupInventoryRecipe();
	SetMachineState(EEFMachineState::Idle);
}

bool AEFMachineBase::CanProcessRecipe()
{
	EFCHECK(nullptr != CurrentRecipe, false);
	
	for (auto ItemCount : CurrentRecipe->InputItem)
	{
		FEFItemInstance Item;
		Item.ItemData = ItemCount.ItemData;
		if (!InputInventory->HasEnoughItem(Item, ItemCount.Quantity))
		{
			return false;
		}
	}
	return true;
}

void AEFMachineBase::ConsumeIngredients()
{
	EFCHECK(nullptr != CurrentRecipe);
	
	for (auto ItemCount : CurrentRecipe->InputItem)
	{
		FEFItemInstance Item;
		Item.ItemData = ItemCount.ItemData;
		InputInventory->RemoveItem(Item, ItemCount.Quantity);
	}
}

void AEFMachineBase::ProduceOutput()
{
	for (auto ItemCount : CurrentRecipe->OutputItem)
	{
		FEFItemInstance Item;
		Item.ItemData = ItemCount.ItemData;
		
		// Set Item Quality
		Item.Quality = 1.0f;
		
		int32 remain = OutputInventory->AddItem(Item, ItemCount.Quantity);
		if (remain >= 0)
		{
			FEFItemStack remainItem;
			remainItem.Item = Item;
			remainItem.Quantity = remain;
			RemainItems.Add(remainItem);
		}
	}
}

void AEFMachineBase::FlushRemainItems()
{
	for (int32 i = RemainItems.Num() - 1; i >= 0; --i)
	{
		int32 remain = OutputInventory->AddItem(RemainItems[i].Item, RemainItems[i].Quantity);
		RemainItems[i].Quantity = remain;
		if (remain <= 0)
		{
			RemainItems.RemoveAt(remain);
		}
	}
}
