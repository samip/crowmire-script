

#pragma once

#include "GameFramework/Actor.h"
#include "UsableActor.generated.h"

class AcrowmireCharacter;

UCLASS()
class CROWMIRE_API AUsableActor : public AActor
{
	GENERATED_BODY()
	
public:
	AUsableActor();
	
	UPROPERTY()
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Collider)
		UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rendering)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
		FString HudText;

	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void OnUseAction();
	virtual void OnUseAction_Implementation();

	virtual void BeginPlay() override;


};
