

#pragma once

#include "UsableActor.h"
#include "DoorBase.generated.h"

/**
 * Handles door opening/closing.
 * (Probably deprecated)
 */
UCLASS()
class CROWMIRE_API ADoorBase : public AUsableActor
{
	GENERATED_BODY()

public:
	ADoorBase();
	void BeginPlay();
	void Tick(float DeltaSeconds);
	


protected:	
	UPROPERTY(Category = Door, VisibleAnywhere, BlueprintReadOnly)
		bool bIsOpen;
		
	UFUNCTION(Category = Door, BlueprintCallable)
		void Open();

	UFUNCTION(Category = Door, BlueprintCallable)
		void Close();

private:
	FRotator Rotator;

	float GetYaw();

	bool bIsOpening;

	bool bIsClosing;

};
