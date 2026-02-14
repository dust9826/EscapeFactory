// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "Components/ActorComponent.h"
#include "EFInventoryComponent.generated.h"

class UEFRecipeDataAsset;
struct FEFItemInstance;
struct FEFItemStack;
struct FEFItemCount;

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
	
public:
	// Machine 레시피 고정에 필요. 상속으로 빼도 될듯.
	void SetupRecipe(TArray<FEFItemCount> ItemCounts);
	
	const TArray<FEFItemStack>& GetSlots();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxSlots = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FEFItemStack> Slots;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	bool bIsLocked = false;
};
