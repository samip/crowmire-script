

#include "crowmire.h"
#include "PickableActor.h"


APickableActor::APickableActor() : AUsableActor()
{
	HasBeenPicked = false;
}

bool APickableActor::CanBePicked()
{
	return !HasBeenPicked;
}

void APickableActor::OnActorPicked_Implementation()
{
}

void APickableActor::Hide()
{
	HasBeenPicked = true;
	MeshComponent->UnregisterComponent();
	BoxComponent->UnregisterComponent();
}