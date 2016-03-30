// Morrow Games 2015-2016

#pragma once
#include "UsableActor.h"
#include "MeshWallText.h"
#include "MeshWallPlane.h"
#include "MeshWall.generated.h"

/**
 Handles Crowmire zone 3 "MeshWall" puzzle.

 When player uses this actor start 2 timers; PuzzleTimer and TextSpawnTimer. 

 Draw random mesh from TextMeshes (initialized from editor) on random AMeshWallPlane whenever TextSpawnTimer elapses.

 Player can remove text with UseKey. Player wins if there are less than TextLimit texts after puzzle time ends.

 */
UCLASS()
class CROWMIRE_API AMeshWall : public AUsableActor
{
	GENERATED_BODY()

public:
	AMeshWall();
	
	void BeginPlay();

	void StartPuzzle();

	/* Blueprint event fired after puzzle has ended */
	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void PuzzleEnded(bool PlayerWon);

	/* Blueprint event fired after each mesh spawn */
	UFUNCTION(BlueprintImplementableEvent, Category = Puzzle)
		void TextSpawned(AMeshWallText* SpawnedText);

	/* Text meshes used in puzzle. Will be drawn in random order */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		TArray<UStaticMesh*> TextMeshes;

	/* Time in seconds before the first text is drawn */
	UPROPERTY(EditAnywhere, Category = Timing)
		float InitialSpawnInterval;

	/* Subtracted from InitialSpawnInterval on each draw event */
	UPROPERTY(EditAnywhere, Category = Timing)
		float SpawnIntervalChange;

	/* Spawn interval will never go below this*/
	UPROPERTY(EditAnywhere, Category = Timing)
		float MinimiumSpawnInterval;

	/* Puzzle duration in seconds */
	UPROPERTY(EditAnywhere, Category = Timing)
		float PuzzleDuration;

	/* How many texts can be left when PuzzleDuration elapses for player to win */
	UPROPERTY(EditAnywhere, Category = Puzzle)
		int32 TextLimit;
	
	/* Puzzle will start automatically if true. Used for testing. */
	UPROPERTY(EditAnywhere, Category = Testing)
		bool StartOnBeginPlay;

	/* Calculate and print time needed to draw all TextMeshes set in editor */
	UPROPERTY(EditAnywhere, Category = Testing)
		bool PrintDebugInfo;

	/* Called when player wants to start the puzzle */
	void OnUseAction_Implementation() override;

	/* Spawn AMeshWallText on AMeshWallPlane. Called automatically every TextSpawnTimer pass */
	void SpawnWallText();

	/* Called when PuzzleTimer elapses */
	void TimeElapsed();

private:
	FTimerHandle TextSpawnTimer;

	FTimerHandle PuzzleTimer;

	/*
	Current interval between text spawns. 
	*/
	float TextSpawnInterval;
	
	/*
	Calculates new TextSpawnInterval and updates TextSpawnTimer to use it.
	*/
	void UpdateTimer();

	/*
	Prints debug info to editor. Irrelevant to gameplay.
	*/
	void DebugInfo();
};
