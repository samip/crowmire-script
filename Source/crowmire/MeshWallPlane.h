// Morrow Games 2015-2016

#pragma once

#include "GameFramework/Actor.h"
#include "MeshWallPlane.generated.h"

/**
 Target for AMeshWallText
*/

UCLASS()
class CROWMIRE_API AMeshWallPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshWallPlane();

	static AMeshWallPlane* GetFreePlane();

	static void InitializeArrays(UWorld* World);

	static void Cleanup();

	UPROPERTY(EditAnywhere, Category = Logic)
		UBoxComponent* Plane;

	/*
	Called when mesh is spawned on this plane or the mesh was destroyed.
	*/
	void SetUsed(bool HasMeshText);

	static int32 GetPlaneCount();

	static int32 GetFreePlaneCount();

private:
	TArray<FVector> TextLocations;

	/*
	All planes without Mesh
	*/
	static TArray<AMeshWallPlane*> FreeActors;

	/*
	All planes in level
	*/
	static TArray<AMeshWallPlane*> SpawnedActors;

	/* Set to true when mesh is spawned on this plane */
	bool HasMeshText;
};
