

#include "crowmire.h"
#include "crowmireCharacter.h"
#include "BotController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotController.h"
#include "BotCharacter.h"



ABotController::ABotController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoradComp"));

	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
}

void ABotController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	ABotCharacter* Botti = Cast<ABotCharacter>(InPawn);

	if (Botti && Botti->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(*Botti->BotBehavior->BlackboardAsset);

		EnemyID = BlackboardComp->GetKeyID("Enemy");
		LastSpottedSpot = BlackboardComp->GetKeyID("LastSpottedPoint");
		State = BlackboardComp->GetKeyID("State");

		BehaviorComp->StartTree(*Botti->BotBehavior);
	}
}

void ABotController::SetEnemy(class APawn* Inpawn)
{
	BlackboardComp->SetValueAsObject(EnemyID, Inpawn);
}

void ABotController::SetLastLocation(class APawn* Inpawn)
{
	BlackboardComp->SetValueAsVector(LastSpottedSpot, Inpawn->GetActorLocation());
}

void ABotController::SetState(uint8 eState)
{
	BlackboardComp->SetValueAsEnum(State, eState);
}

FVector ABotController::GetLastSpottedPoint()
{
	return BlackboardComp->GetValueAsVector(LastSpottedSpot);
}
