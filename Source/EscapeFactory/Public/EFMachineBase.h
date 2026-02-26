// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeFactory.h"
#include "GameFramework/Actor.h"
#include "EFInteractable.h"
#include "EFMachineBase.generated.h"

class UEFInventoryComponent;
class UEFRecipeDataAsset;
struct FEFItemStack;

DECLARE_MULTICAST_DELEGATE(FOnMachineRecipeSelected);

UENUM(BlueprintType)
enum class EEFMachineState : uint8
{
	SelectingRecipe    UMETA(DisplayName = "레시피 선택"),
	Idle               UMETA(DisplayName = "대기"),
	Working            UMETA(DisplayName = "작동"),
	Paused             UMETA(DisplayName = "정지")
};

UCLASS()
class ESCAPEFACTORY_API AEFMachineBase : public AActor, public IEFInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEFMachineBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor) override;
	virtual FString GetInteractName() const override;
	
protected:
	void UpdateProduction(float DeltaTime);
	
	void SetupInventoryRecipe();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Machine State")
	void SetMachineState(EEFMachineState NewState);

	UFUNCTION(BlueprintCallable, Category = "Machine State")
	void SelectRecipe(UEFRecipeDataAsset* NewRecipe);
	
private:
	bool CanProcessRecipe();
	void ConsumeIngredients();
	void ProduceOutput();
	void FlushRemainItems();
	
public:
	FOnMachineRecipeSelected OnMachineRecipeSelected;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Machine | Production")
	float CurrentProgress = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine | Production")
	UEFRecipeDataAsset* CurrentRecipe;
	
	UPROPERTY(VisibleAnywhere, Category = "Machine | Production")
	TArray<FEFItemStack> RemainItems;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UEFInventoryComponent* InputInventory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UEFInventoryComponent* OutputInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine | State")
	EEFMachineState CurrentState = EEFMachineState::SelectingRecipe;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine | Layout")
	FIntPoint GridSize = FIntPoint(3, 3); // 기본값 3x3
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine")
	UStaticMeshComponent* StaticMesh; // 기본값 3x3
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Machine")
	FString MachineName;
	
	UPROPERTY(EditAnywhere, Category = "Machine | Production", meta = (AllowPrivateAccess = "true"))
	TArray<UEFRecipeDataAsset*> AvailableRecipes;
	
public:
	UEFInventoryComponent* GetInputInventoryComponent() { return InputInventory; }
	UEFInventoryComponent* GetOutputInventoryComponent() { return OutputInventory; }
	EEFMachineState GetMachineState() { return CurrentState; }
	TArray<UEFRecipeDataAsset*> GetAvailableRecipes() { return AvailableRecipes; }
	float GetCurrentProgress() { return CurrentProgress; }
	UEFRecipeDataAsset* GetCurrentRecipe() { return CurrentRecipe; }
};
