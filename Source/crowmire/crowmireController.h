#pragma once

#include "GameFramework/PlayerController.h"
#include "crowmireController.generated.h"

/**
 * 
 */

class AFocusableActor;

UCLASS()
class CROWMIRE_API AcrowmireController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetFocus(AFocusableActor* Actor);
	void FocusOnCharacter();
	
private:
	AFocusableActor* FocusedActor;
	
};
