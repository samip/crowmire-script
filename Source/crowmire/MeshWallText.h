// Morrow Games 2015-2016

#pragma once
#include "Kismet/KismetMathLibrary.h"
#include "UsableActor.h"
#include "MeshWallPlane.h"
#include "MeshWallText.generated.h"

/**
  Actor to be spawned on AMeshWallPlane.
  Player can destroy these with UseKey. 
 */

class AMeshWall;

UCLASS()
class CROWMIRE_API AMeshWallText : public AUsableActor
{
	GENERATED_BODY()

public:
	static void InitializeMeshes(TArray<UStaticMesh*> Meshes);

	static void Cleanup(UWorld* World);

	static AMeshWallText* Spawn(AMeshWallPlane* Plane);

	UFUNCTION(BlueprintCallable, Category = Rendering)
		UStaticMesh* GetMesh();

	static int32 GetSpawnedCount();

	static int32 GetUnusedMeshCount();

	void SetMesh(UStaticMesh* Mesh);

	void SetHostPlane(AMeshWallPlane* HostPlane);

	void OnUseAction_Implementation() override;

private:
	AMeshWallPlane* HostPlane;

	static int32 SpawnedCount;

	static TArray<UStaticMesh*> MeshPool;
};
