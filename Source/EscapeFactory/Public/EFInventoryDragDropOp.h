#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "EFInventoryDragDropOp.generated.h"

/**
 * 드래그 중인 아이템의 정보를 담고 있는 데이터 객체입니다.
 */
UCLASS()
class ESCAPEFACTORY_API UEFInventoryDragDropOp : public UDragDropOperation
{
	GENERATED_BODY()

	void DragCancelled_Implementation(const FPointerEvent& PointerEvent) override;
	
public:
	UPROPERTY(BlueprintReadWrite)
	class UEFInventorySlotWidget* SourceSlotWidget;
};