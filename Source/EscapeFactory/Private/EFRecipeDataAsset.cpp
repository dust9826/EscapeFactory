// Fill out your copyright notice in the Description page of Project Settings.


#include "EFRecipeDataAsset.h"

FPrimaryAssetId UEFRecipeDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("EFRecipe"), GetFName());
}
