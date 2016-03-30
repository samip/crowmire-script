// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "crowmire.h"
#include "HudTextActor.h"
#include "FocusableActor.h"
#include "UsableActor.h"
#include "PickableActor.h"
#include "crowmireCharacter.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AcrowmireCharacter

AcrowmireCharacter::AcrowmireCharacter()
{
	Input = NULL;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	
	PrimaryActorTick.bCanEverTick = true;
}

void AcrowmireCharacter::BeginPlay()
{
	Super::BeginPlay();
	HudActor = GetWorld()->SpawnActor<AHudTextActor>(AHudTextActor::StaticClass());
}


//////////////////////////////////////////////////////////////////////////
// Input

void AcrowmireCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	if (Input == NULL)
	{
		this->Input = InputComponent;
	}

	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Use", IE_Pressed, this, &AcrowmireCharacter::Use);
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AcrowmireCharacter::ShowInventory);

	InputComponent->BindAxis("MoveForward", this, &AcrowmireCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AcrowmireCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AcrowmireCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AcrowmireCharacter::LookUpAtRate);
	
}



void AcrowmireCharacter::Use()
{
	//TArray<AActor*> OverlappingActors;
	AUsableActor* usable;
	AFocusableActor* focusable;
	APickableActor* pickable;

	//GetOverlappingActors(OverlappingActors, TSubclassOf<AActor>());

	AActor* RayhitActor = Rayhit.GetActor();

	usable = dynamic_cast<AUsableActor*>(RayhitActor);
	if (usable != nullptr)
	{
		focusable = dynamic_cast<AFocusableActor*>(usable);
		// actor was focusable actor
		if (focusable != nullptr)
		{
			AcrowmireController* controller = (AcrowmireController*)GetWorld()->GetFirstPlayerController();
			controller->SetFocus(focusable);
			//continue;
		}

		pickable = dynamic_cast<APickableActor*>(usable);
		// actor was pickable actor
		if (pickable != nullptr)
		{
			if (pickable->CanBePicked())
			{
				this->Inventory.Add(pickable);
				pickable->OnActorPicked();
				pickable->Hide();
			}
		}
		usable->OnUseAction();
	}
}

//Raycast
void AcrowmireCharacter::GetUsableActor(FHitResult* Hit, FCollisionQueryParams* Params)
{
	float TraceLength = 150;
	FVector CamLoc;
	FRotator CamRot;
	Controller->GetPlayerViewPoint(CamLoc, CamRot);

	FVector Start = CamLoc;
	FVector Direction = CamRot.Vector();
	FVector End = Start + Direction * TraceLength;

	AActor* RayhitActor = Rayhit.GetActor();
	AUsableActor* usable;
	usable = dynamic_cast<AUsableActor*>(RayhitActor);
	
	Params->bTraceAsyncScene = true;
	Params->bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility, *Params);

	if (usable != nullptr)
	{
		HudActor->TextComponent->SetText(usable->HudText);
		HudActor->TextComponent->SetVisibility(true);

		if (HudActor->InfoTextComponent->IsVisible() == true)
		{
			HudActor->TextComponent->SetVisibility(false);
		}
	}
	else
	{
		HudActor->TextComponent->SetVisibility(false);
	}
}

void AcrowmireCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FCollisionQueryParams RayTraceParams = FCollisionQueryParams(FName(TEXT("RayTrace")), true, this);
	GetUsableActor(&Rayhit, &RayTraceParams);
}

//update HUDTextActor position
void AcrowmireCharacter::UpdateHudPosition(FVector Start, FVector Direction, FRotator CamRot)
{
	FVector End = (Start - FVector(0, 0, 5)) + Direction * 14;

	FTransform HudNewTransform(CamRot, End);
	HudActor->SetActorTransform(HudNewTransform);
}


//set HudTextActor visibility
void AcrowmireCharacter::ShowHudInfo(FString text)
{
	HudActor->InfoTextComponent->SetText(text);
	HudActor->InfoTextComponent->SetVisibility(true);
}


//set HudTextActor visibility
void AcrowmireCharacter::HideHudInfo()
{
	HudActor->InfoTextComponent->SetVisibility(false);
}


void AcrowmireCharacter::ShowInventory()
{

}

void AcrowmireCharacter::AddItem(APickableActor* Item)
{
	Inventory.Add(Item);
}


TArray<APickableActor*> AcrowmireCharacter::GetInventoryItems()
{
	return Inventory.GetItems();
}


bool AcrowmireCharacter::HasItem(APickableActor* Item)
{
	return Inventory.GetItems().Find(Item) != INDEX_NONE;
}


// todo: inventory luokka publiciks ja näiden methodien poisto
void AcrowmireCharacter::SetItems(TArray<APickableActor*> Items)
{
	Inventory.SetItems(Items);
}


void AcrowmireCharacter::Remove(APickableActor* Item)
{
	Inventory.Remove(Item);
}


void AcrowmireCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AcrowmireCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void AcrowmireCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}


void AcrowmireCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
