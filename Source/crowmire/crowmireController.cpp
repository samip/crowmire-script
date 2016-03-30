#pragma once

#include "crowmire.h"
#include "crowmireCharacter.h"
#include "FocusableActor.h"
#include "crowmireController.h"




void AcrowmireController::SetFocus(AFocusableActor* actor)
{
	print("Setting focus to " + actor->GetName());
	
	if (actor->hasCamera())
	{
		SetViewTarget(actor);
	}
	else
	{
		print("no camera");
	}


	actor->EnableInput(this);
	actor->SetupInput();
	FocusedActor = actor;
}


void AcrowmireController::FocusOnCharacter()
{
	AcrowmireCharacter* Character = (AcrowmireCharacter*) UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Character->EnableInput(this);
	FocusedActor->DisableInput(this);

	SetViewTarget(Character);
	print("Going back from " + FocusedActor->GetName());
}
