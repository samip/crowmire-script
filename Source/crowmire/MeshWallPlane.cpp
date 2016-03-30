// Morrow Games 2015-2016

#include "crowmire.h"
#include "MeshWallPlane.h"

TArray<AMeshWallPlane*> AMeshWallPlane::SpawnedActors;
TArray<AMeshWallPlane*> AMeshWallPlane::FreeActors;


AMeshWallPlane::AMeshWallPlane()
{
	PrimaryActorTick.bCanEverTick = false;

	// build plane component
	Plane = CreateDefaultSubobject<UBoxComponent>(TEXT("Plane"));
	Plane->SetRelativeScale3D(FVector(2, 0, 2));
	Plane->bHiddenInGame = false;
	RootComponent = Plane;
}


void AMeshWallPlane::InitializeArrays(UWorld* World)
{
	FreeActors.Empty();
	SpawnedActors.Empty();
	for (TActorIterator<AMeshWallPlane> ActorItr(World); ActorItr; ++ActorItr)
	{
		SpawnedActors.Add(*ActorItr);
		FreeActors.Add(*ActorItr);
	}
}

/*
	Remove all actors
*/
void AMeshWallPlane::Cleanup()
{
	SpawnedActors.Empty();
	FreeActors.Empty();
}

int32 AMeshWallPlane::GetPlaneCount()
{
	return SpawnedActors.Num();
}


int32 AMeshWallPlane::GetFreePlaneCount()
{
	return FreeActors.Num();
}

/*
	Return random Plane from FreeActors
*/
AMeshWallPlane* AMeshWallPlane::GetFreePlane()
{
	// This macro executes the expression and, if it results in a false assertion, halts execution.
	check(FreeActors.Num() > 0);
	int32 WallIndex = FMath::RandRange(0, AMeshWallPlane::FreeActors.Num() - 1);
	return AMeshWallPlane::FreeActors[WallIndex];
}

/*
	Set HashMesText and update FreeActors array
*/
void AMeshWallPlane::SetUsed(bool HasMeshText)
{
	if (HasMeshText)
	{
		FreeActors.Remove(this);
	}
	else
	{
		FreeActors.Add(this);
	}
	this->HasMeshText = HasMeshText;
}