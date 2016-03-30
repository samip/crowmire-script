// Morrow Games 2015-2016

/**
 *	Used to render HUD text in 3D space because normal UMG widgets dont work Oculus
 */

#pragma once

#include "GameFramework/Actor.h"
#include "HudTextActor.generated.h"

UCLASS()
class CROWMIRE_API AHudTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHudTextActor();
	
	UPROPERTY()
		USceneComponent* SceneComponent;

	UPROPERTY()
		UTextRenderComponent* TextComponent;
	
	UPROPERTY()
		UTextRenderComponent* InfoTextComponent;
};
