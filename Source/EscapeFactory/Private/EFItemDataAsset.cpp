// Fill out your copyright notice in the Description page of Project Settings.


#include "EFItemDataAsset.h"

FPrimaryAssetId UEFItemDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("EFItem"), GetFName());
}
