#include "crowmire.h"
#include "FocusableActor.h"

AFocusableActor::AFocusableActor() : AUsableActor()
{
	//
}

void AFocusableActor::BeginPlay()
{
	CameraComponent = GetCameraComponent();
}


void AFocusableActor::OnUseAction()
{

}


void AFocusableActor::SetupInput()
{
	//
}


bool AFocusableActor::hasCamera()
{
	return GetCameraComponent() != NULL;
}


UCameraComponent* AFocusableActor::GetCameraComponent()
{
	TArray<UCameraComponent*> CameraComponents;
	GetComponents(CameraComponents);

	if (CameraComponents.Num() == 0)
	{
		return NULL;
	}

	return CameraComponents[0];
}


void AFocusableActor::LoseFocus()
{
	AcrowmireController* controller = (AcrowmireController*) GetWorld()->GetFirstPlayerController();
	controller->FocusOnCharacter();
}