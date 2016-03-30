// Morrow Games 2015-2016

#include "crowmire.h"
#include "HudTextActor.h"


// Sets default values
AHudTextActor::AHudTextActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HudText"));
	InfoTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InfoText"));
	RootComponent = SceneComponent;
	
	TextComponent->SetWorldSize(0.9);
	TextComponent->SetRelativeRotation(FRotator(0, 180, 0));

	InfoTextComponent->SetWorldSize(0.9);
	InfoTextComponent->SetRelativeRotation(FRotator(0, 180, 0));
	InfoTextComponent->SetRelativeLocation(FVector(0, -2, 0));

	TextComponent->SetVisibility(false);
	InfoTextComponent->SetVisibility(false);

	TextComponent->AttachTo(RootComponent);
	InfoTextComponent->AttachTo(RootComponent);
}


