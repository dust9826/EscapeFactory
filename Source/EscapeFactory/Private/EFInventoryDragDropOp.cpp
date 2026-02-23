#include "EFInventoryDragDropOp.h"

#include "EFInventorySlotWidget.h"
#include "EFItemVisualWidget.h"
#include "EFPlayerController.h"

void UEFInventoryDragDropOp::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
	Super::DragCancelled_Implementation(PointerEvent);
	
	if (SourceSlotWidget)
	{
		if (AEFPlayerController* PC = Cast<AEFPlayerController>(SourceSlotWidget->GetOwningPlayer()))
		{
			if (PC->ItemVisualWidget)
			{
				PC->ItemVisualWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}
