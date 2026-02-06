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
	
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 BaseValue = 1;
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

USTRUCT(BlueprintType)
struct FEFItemInstance
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UEFItemDataAsset* ItemData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Quality;
	
	FEFItemInstance() : ItemData(nullptr), Quality(1.0f) {}
	float GetCurrentValue() const
	{
		return ItemData ? ItemData->BaseValue * Quality : 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FEFItemStack
{
	GENERATED_BODY()

	// 이제 ItemData를 따로 두지 않고, Instance 안에 포함된 것을 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEFItemInstance Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;

	FEFItemStack() : Item(), Quantity(0) {}
	
	// 중첩(Stacking) 가능 여부 체크 도우미
	bool CanStackWith(const FEFItemStack& Other) const {
		// 아이템 종류가 같고, 품질이 완벽히 같을 때만 Stack
		return Item.ItemData == Other.Item.ItemData && FMath::IsNearlyEqual(Item.Quality, Other.Item.Quality);
	}
	
	// 중첩(Stacking) 가능 여부 체크 도우미
	bool CanStackWith(const FEFItemInstance& Other) const {
		// 아이템 종류가 같고, 품질이 완벽히 같을 때만 Stack
		return Item.ItemData == Other.ItemData && FMath::IsNearlyEqual(Item.Quality, Other.Quality);
	}
	
	bool IsEmpty() const
	{
		return Item.ItemData == nullptr || Quantity == 0;
	}
};