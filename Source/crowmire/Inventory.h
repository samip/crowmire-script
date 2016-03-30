

#pragma once

#include "PickableActor.h"


/**
 * Wrapper for inventory array
 */


class CROWMIRE_API Inventory
{
public:
	void Add(APickableActor* Item);
	void Remove(APickableActor* Item);

	UFUNCTION()
		TArray<APickableActor*> GetItems();

	/* used after loading saved game */
	UFUNCTION()
		void SetItems(TArray<APickableActor*> Items);

private:
	TArray<APickableActor*> InventoryItems;
};
