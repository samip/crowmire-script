

#pragma once

#include "UsableActor.h"
#include "PickableActor.generated.h"

/**
 * 
 */
UCLASS()
class CROWMIRE_API APickableActor : public AUsableActor
{
	GENERATED_BODY()

public:
	APickableActor();

	bool CanBePicked();

	/* Texture to be drawn in HUD when item has been picked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		UTexture2D* InventoryItem;

	void OnPicked();

	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void OnActorPicked();
	void OnActorPicked_Implementation();

	void Hide();


private:
	bool HasBeenPicked;
};
