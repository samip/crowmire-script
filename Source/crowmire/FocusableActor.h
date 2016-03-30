#pragma once

#include "UsableActor.h"
#include "crowmireController.h"
#include "FocusableActor.generated.h"

/**
 Base class for actors cabable of taking focus (input and possibly camera view) from player controller
*/

UCLASS()
class CROWMIRE_API AFocusableActor : public AUsableActor
{
	GENERATED_BODY()

public:
	AFocusableActor();

	void BeginPlay() override;

	bool hasCamera();

	virtual void SetupInput();

protected:
	UCameraComponent* CameraComponent;

	UCameraComponent* AFocusableActor::GetCameraComponent();

	void LoseFocus();
};
