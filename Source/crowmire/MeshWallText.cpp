// Morrow Games 2015-2016

#include "crowmire.h"
#include "MeshWallText.h"

int32 AMeshWallText::SpawnedCount;
TArray<UStaticMesh*> AMeshWallText::MeshPool;


void AMeshWallText::InitializeMeshes(TArray<UStaticMesh*> Meshes)
{
	AMeshWallText::SpawnedCount = 0;
	MeshPool.Empty();
	for (auto Mesh : Meshes)
	{
		MeshPool.Add(Mesh);
	}
}

void AMeshWallText::Cleanup(UWorld* World)
{
	MeshPool.Empty();
	// destroy all actors of this class
	for (TActorIterator<AMeshWallText> ActorItr(World); ActorItr; ++ActorItr)
	{
		ActorItr->Destroy();
	}
}

AMeshWallText* AMeshWallText::Spawn(AMeshWallPlane* Plane)
{
	FVector Location = Plane->GetActorLocation();
	FRotator Rotator = Plane->GetActorRotation();
	UStaticMesh* Mesh = MeshPool.Pop();
	UWorld* World = Plane->GetWorld();

	AMeshWallText* Instance = (AMeshWallText*)World->SpawnActor(AMeshWallText::StaticClass(), &Location, &Rotator);
	check(Instance != nullptr && Instance->IsValidLowLevel());
	Instance->SetMesh(Mesh);
	Instance->SetHostPlane(Plane);
	Plane->SetUsed(true);
	++AMeshWallText::SpawnedCount;
	return Instance;
}


UStaticMesh* AMeshWallText::GetMesh()
{
	return MeshComponent->StaticMesh;
}


int32 AMeshWallText::GetSpawnedCount()
{
	return AMeshWallText::SpawnedCount;
}


int32 AMeshWallText::GetUnusedMeshCount()
{
	return MeshPool.Num();
}


void AMeshWallText::SetMesh(UStaticMesh* Mesh)
{
	MeshComponent->SetStaticMesh(Mesh);
}


void AMeshWallText::SetHostPlane(AMeshWallPlane* HostPlane)
{
	this->HostPlane = HostPlane;
}

/*
	Called when user selects this mesh. Destroy actor and free it's host.
*/
void AMeshWallText::OnUseAction_Implementation()
{
	// free the host
	this->HostPlane->SetUsed(false);
	this->HostPlane = nullptr;
	GetWorld()->DestroyActor(this);
}
