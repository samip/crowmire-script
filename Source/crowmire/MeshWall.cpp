// Morrow Games 2015-2016

#include "crowmire.h"
#include "MeshWall.h"


AMeshWall::AMeshWall() : AUsableActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("StaticMesh'/Game/Assets/Hospital_logo/SM_Logocrowmire.SM_Logocrowmire'"));
	MeshComponent->SetStaticMesh(DefaultMesh.Object);
	PrimaryActorTick.bCanEverTick = false;
	
	// default values for editor-set variables
	InitialSpawnInterval = 1.0f;
	SpawnIntervalChange = 0.0f;
	MinimiumSpawnInterval = 0.0f;
	PuzzleDuration = 10.0f;
	StartOnBeginPlay = false;
}


void AMeshWall::BeginPlay()
{
	if (PrintDebugInfo)
	{
		DebugInfo();
	}
	if (StartOnBeginPlay)
	{
		StartPuzzle();
	}
}

/*
	Calculates how long after all meshes have been drawn and print it
*/

void AMeshWall::DebugInfo()
{
	AMeshWallPlane::InitializeArrays(GetWorld());
	AMeshWallText::InitializeMeshes(TextMeshes);
	float MeshesUsedAfter = 0;
	float WallsUsedAFter = 0;
	float ActualPuzzleTime = 0;
	float interval = InitialSpawnInterval;
	int32 i = 0;
	
	while (i < AMeshWallText::GetUnusedMeshCount())
	{
		interval = InitialSpawnInterval - (i * SpawnIntervalChange);
		if (interval < MinimiumSpawnInterval)
		{
			interval = MinimiumSpawnInterval;
		}
		ActualPuzzleTime += interval;
		++i;
	}

	MeshesUsedAfter = ActualPuzzleTime;
	float Interval = InitialSpawnInterval;
	float Change = 0;

	FColor MessageColor = (MeshesUsedAfter < PuzzleDuration) ? FColor::Yellow : FColor::Green;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, MessageColor, FString::Printf(TEXT("All %i meshes will be used after %f seconds (puzzle duration %f)"), 
		AMeshWallText::GetUnusedMeshCount(), MeshesUsedAfter, PuzzleDuration));
}


void AMeshWall::StartPuzzle()
{
	AMeshWallPlane::InitializeArrays(GetWorld());
	AMeshWallText::InitializeMeshes(TextMeshes);

	if (AMeshWallPlane::GetPlaneCount() == 0)
	{
		print("MeshWall.cpp: No walls");
	}
	else if (AMeshWallText::GetUnusedMeshCount() == 0)
	{
		print("MeshWall.cpp: Textmeshes uninitialized in MeshWall.");
	}
	else
	{
		TextSpawnInterval = InitialSpawnInterval;
		GetWorld()->GetTimerManager().SetTimer(TextSpawnTimer, this, &AMeshWall::SpawnWallText, TextSpawnInterval, false);
		GetWorld()->GetTimerManager().SetTimer(PuzzleTimer, this, &AMeshWall::TimeElapsed, PuzzleDuration, false);
	}
}


/*
	Start the puzzle on UseKey action
*/

void AMeshWall::OnUseAction_Implementation()
{
	StartPuzzle();
}

void AMeshWall::SpawnWallText()
{
	if (AMeshWallText::GetUnusedMeshCount() == 0)
	{
		FString::FromInt(AMeshWallText::GetSpawnedCount());
		print("All meshes have been used");
		return;
	}

	if (AMeshWallPlane::GetFreePlaneCount() == 0)
	{
		print("All planes in use");
		return;
	}

	AMeshWallPlane* TargetPlane = AMeshWallPlane::GetFreePlane();
	AMeshWallText* WallText = AMeshWallText::Spawn(TargetPlane);
	TextSpawned(WallText);
	UpdateTimer();
}


/*
	Called automatically after puzzle timer elapses.
	Clear timers, calculate result, fires PuzzleEnded blueprint event.
*/

void AMeshWall::TimeElapsed()
{
	print("Time's up");
	GetWorldTimerManager().ClearTimer(TextSpawnTimer);
	GetWorldTimerManager().ClearTimer(PuzzleTimer);
	
	AMeshWallPlane::Cleanup();
	AMeshWallText::Cleanup(GetWorld());

	int32 ExistingTextes = AMeshWallPlane::GetPlaneCount() - AMeshWallPlane::GetFreePlaneCount();
	bool PlayerWon = ExistingTextes <= TextLimit;
	print(PlayerWon ? "Won" : "lost");
	// fire bp event
	PuzzleEnded(PlayerWon);
}

/*
	Calculate new spawn interval and update timer
*/

void AMeshWall::UpdateTimer()
{
	 TextSpawnInterval -= SpawnIntervalChange;
	if (TextSpawnInterval < MinimiumSpawnInterval)
	{
		TextSpawnInterval = MinimiumSpawnInterval;
	}
	GetWorld()->GetTimerManager().SetTimer(TextSpawnTimer, this, &AMeshWall::SpawnWallText, TextSpawnInterval, false);
}