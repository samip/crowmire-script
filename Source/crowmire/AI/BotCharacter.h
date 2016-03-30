

#pragma once

#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

UCLASS()
class CROWMIRE_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()
	ABotCharacter();

public:

	UPROPERTY(EditAnyWhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnyWhere, Category = AI)
	class UPawnSensingComponent* BotSensingComp;
	
	UPROPERTY(BlueprintReadOnly, Category = AI)
	bool bTargetSpotted;

	bool bLastLocation;

	float LastSpottedTime;

	float TimeOut;	
	
	virtual void BeginPlay() override;	
	
	virtual void Tick(float DeltaSeconds) override;

private:

	UFUNCTION()
	void OnSeePlayer(class APawn* Pawn);
};
