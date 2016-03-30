#include "crowmire.h"
#include "UsableActor.h"


AUsableActor::AUsableActor() : AActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	
	SceneComponent->SetRelativeLocation(FVector::ZeroVector);

	RootComponent = SceneComponent;
	BoxComponent->AttachTo(RootComponent);
	MeshComponent->AttachTo(RootComponent);
}


void AUsableActor::BeginPlay()
{
	Super::BeginPlay();
}


void AUsableActor::OnUseAction_Implementation()
{

}
