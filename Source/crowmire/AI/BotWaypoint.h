

#pragma once

#include "Engine/TargetPoint.h"
#include "BotWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class CROWMIRE_API ABotWaypoint : public ATargetPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, Category = Position)
	uint8 Position;
	
	
};
