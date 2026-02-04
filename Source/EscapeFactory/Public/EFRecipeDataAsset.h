// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EFRecipeDataAsset.generated.h"

class UEFItemDataAsset;

USTRUCT(BlueprintType)
struct FEFRecipeIngredient
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEFItemDataAsset* ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity;
};

/**
 *
 */
UCLASS()
class ESCAPEFACTORY_API UEFRecipeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	TArray<FEFRecipeIngredient> Ingredients;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	UEFItemDataAsset* OutputItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	int32 OutputQuantity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	float ProductionTime = 1.0f;
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
