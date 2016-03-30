#pragma once

#include "crowmire.h"
#include "crowmireCharacter.h"
#include "FocusableActor.h"
#include "crowmireController.h"




void AcrowmireController::SetFocus(AFocusableActor* Actor)
{
	print("Setting focus to " + Actor->GetName());
	
	if (Actor->hasCamera())
	{
		SetViewTarget(Actor);
	}
	else
	{
		print("No camera");
	}

	Actor->EnableInput(this);
	Actor->SetupInput();
	FocusedActor = Actor;
}


void AcrowmireController::FocusOnCharacter()
{
	AcrowmireCharacter* Character = (AcrowmireCharacter*) UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Character->EnableInput(this);
	FocusedActor->DisableInput(this);

	SetViewTarget(Character);
	print("Going back from " + FocusedActor->GetName());
}
