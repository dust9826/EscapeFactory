// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFInteractable.h"
#include "EFItemDataAsset.h"
#include "GameFramework/Actor.h"
#include "EFDropItemActor.generated.h"

UCLASS()
class ESCAPEFACTORY_API AEFDropItemActor : public AActor, public IEFInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEFDropItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Interact(AActor* Interactor) override;
	virtual FString GetInteractName() const override;
	
public:
	void InitializeDrop(const FEFItemStack& InStack);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FEFItemStack ItemStack;
	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;
};
