

#pragma once
#include "AIController.h"
#include "BotController.generated.h"

/**
 * 
 */
UCLASS()
class CROWMIRE_API ABotController : public AAIController
{
	GENERATED_BODY()
	
	ABotController(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorComp;

	virtual void Possess(class APawn* InPawn);

public:
	void SetEnemy(class APawn* InPawn);

	void SetLastLocation(class APawn* InPawn);

	void SetState(uint8 State);

	FVector GetLastSpottedPoint();

protected:
	uint8 EnemyID;
	uint8 LastSpottedSpot;
	uint8 State;
};
