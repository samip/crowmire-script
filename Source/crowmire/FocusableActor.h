#pragma once

#include "UsableActor.h"
#include "crowmireController.h"
#include "FocusableActor.generated.h"


UCLASS()
class CROWMIRE_API AFocusableActor : public AUsableActor
{
	GENERATED_BODY()

public:
	AFocusableActor();
	void BeginPlay() override;
	void OnUseAction();
	bool hasCamera();
	virtual void SetupInput();

protected:
	UCameraComponent* CameraComponent;
	UCameraComponent* AFocusableActor::GetCameraComponent();

	void LoseFocus();

};
