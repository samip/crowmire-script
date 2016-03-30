#include "crowmire.h"
#include "Patient.h"




APatient::APatient() : AUsableActor()
{

	static ConstructorHelpers::FObjectFinder <UStaticMesh>PatientMesh(TEXT("StaticMesh'/Game/Assets/Xrayroom/SM_Ukkeli/läski_ukkeli_v8_optimizered.läski_ukkeli_v8_optimizered'"));
	MeshComponent->SetRelativeRotation(FRotator(0, 0, 90));
	MeshComponent->SetStaticMesh(PatientMesh.Object);

	StitchSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("StitchScene"));
	StitchSceneComponent->SetRelativeLocation(FVector::ZeroVector);
	StitchSceneComponent->AttachTo(RootComponent);
	


	Stitches.Add("Hip", &Hip);
	Stitches.Add("RightArm", &RightArm);
	Stitches.Add("LeftArm", &LeftArm);
	Stitches.Add("Chest", &Chest);

	FString StitchMeshFolder = "StaticMesh'/Game/Blueprints/XrayPuzzle/Stitches/";

	int i = 0;
	for (auto& Elem : Stitches)
	{
		FString Name = Elem.Key;
		FString StitchMeshPath = FString::Printf(TEXT("%s/%s.%s'"), *StitchMeshFolder, *Name, *Name);
		UStaticMeshComponent* Temp = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("ModelComp%d"), i));
		Temp->AttachTo(StitchSceneComponent);
	
		FString MeshString = FString::Printf(TEXT("%s%s.%s'"), *StitchMeshFolder, *Name, *Name);
		Temp->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MeshString).Object);
		Temp->SetRelativeLocation(FVector::ZeroVector);
		*Elem.Value = Temp;
		i++;
	}
}

void APatient::BeginPlay()
{
	int32 StitchCount = Stitches.Num();
	KeyStitchIndex = FMath::RandRange(0, StitchCount - 1);
}
void APatient::SetKeyStitchIndex(uint8 KeyStitchIndex)
{
	KeyStitchIndex = KeyStitchIndex;
}



void APatient::OnStitchSelected_Implementation(bool WasCorrect)
{
	print("Missing patient OnStitchSelected BP");
}

uint8 APatient::GetKeyStitchIndex()
{
	return KeyStitchIndex;
}