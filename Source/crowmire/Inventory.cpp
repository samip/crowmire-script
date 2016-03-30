

#include "crowmire.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Add(APickableActor* Item)
{
	InventoryItems.Add(Item);
}

void Inventory::Remove(APickableActor* Item)
{
	InventoryItems.Remove(Item);
}

TArray<APickableActor*> Inventory::GetItems()
{
	return InventoryItems;
}

void Inventory::SetItems(TArray<APickableActor*> Items)
{
	InventoryItems = Items;
}