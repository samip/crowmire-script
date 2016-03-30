

#include "crowmire.h"
#include "crowmireCharacter.h"
#include "BotCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BotController.h"

// Sets default values
ABotCharacter::ABotCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABotController::StaticClass();

	BotSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("BotSensingComp"));

	TimeOut = 1.0f;
}

void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (BotSensingComp)
	{
		BotSensingComp->OnSeePawn.AddDynamic(this, &ABotCharacter::OnSeePlayer);
	}
	
}

void ABotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTargetSpotted && (GetWorld()->TimeSeconds - LastSpottedTime) > TimeOut)
	{
		ABotController* BotController = Cast<ABotController>(GetController());
		AcrowmireCharacter* Enemy = Cast<AcrowmireCharacter>(GWorld->GetFirstPlayerController()->GetPawn());

		if (BotController)
		{
			bTargetSpotted = false;

			BotController->SetEnemy(NULL);

			BotController->SetLastLocation(Enemy);
			BotController->SetState(1);
			bLastLocation = true;		
		}
	}

	if (bTargetSpotted == false && bLastLocation == true)
	{
		ABotController* BotController = Cast<ABotController>(GetController());
		if ((this->GetActorLocation() - BotController->GetLastSpottedPoint()).Size() <= 100.0f)
		{
			BotController->SetState(0);
			bLastLocation = false;
		}
	}
}

void ABotCharacter::OnSeePlayer(class APawn* Pawn)
{
	bTargetSpotted = true;
	LastSpottedTime = GetWorld()->GetTimeSeconds();

	ABotController* BotController = Cast<ABotController>(GetController());

	AcrowmireCharacter* Enemy = Cast<AcrowmireCharacter>(Pawn);

	if (BotController)
	{
		BotController->SetEnemy(Enemy);
		BotController->SetState(2);
	}
}



