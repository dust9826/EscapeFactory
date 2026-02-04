// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EFItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFACTORY_API UEFItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	FName ItemName;
	
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 MaxStackSize = 99;
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

USTRUCT(BlueprintType)
struct FEFItemSlot
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UEFItemDataAsset* ItemData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Quantity;
	
	FEFItemSlot() : ItemData(nullptr), Quantity(0) {}
	bool IsEmpty() const {return ItemData == nullptr || Quantity == 0;}
};