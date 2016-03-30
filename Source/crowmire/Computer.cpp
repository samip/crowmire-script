#include "crowmire.h"
#include "Computer.h"


AComputer::AComputer() : AFocusableActor()
{
	InputDelayInSeconds = .5;
	CurrentPictureIndex = 0;
}


void AComputer::SetupInput()
{
	UInputComponent* InputComp = InputComponent;
	
	if (!InputComp)
	{
		print("Invalid InputComponent in" + GetName());
		return;
	}

	InputComponent->BindAction("Use", IE_Pressed, this, &AComputer::LoseFocus);
	InputComponent->BindAxis("MoveRight", this, &AComputer::Browse);
}

void AComputer::SetImageArray()
{
	if (TargetPatient == nullptr)
	{
		print("Computer: TargetPatient null");
		KeyStitchIndex = 0;
	}
	else
	{
		print("ok");
		KeyStitchIndex = TargetPatient->GetKeyStitchIndex();

	}
	print(FString::FromInt(KeyStitchIndex));
	FString Folder = "Texture2D'/Game/Blueprints/XrayPuzzle/xraypicture/";

	TArray<FString> XrayImageFiles;
	XrayImageFiles.Add("XRayHip");
	XrayImageFiles.Add("XRayHandR");
	XrayImageFiles.Add("XRayHandL");
	XrayImageFiles.Add("XRayChest");

	for (int i = 0; i < XrayImageFiles.Num(); i++)
	{
		FString TextureName = XrayImageFiles[i];
		FString TextureString = FString::Printf(TEXT("%s%s.%s'"), *Folder, *TextureName, *TextureName);
		FString TextureKeyString = FString::Printf(TEXT("%s%s.%s'"), *Folder, *TextureName, *(TextureName).Append("_key"));

		XrayImages.Add(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(TextureString))));
		XrayKeyImages.Add(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(TextureKeyString))));
	}
	ImagesSet = true;
}

void AComputer::BeginPlay()
{
	InputEnabled = true;
}


void AComputer::Browse(float Value)
{
	float Epsilon = 0.0005;
	uint8 LastPictureIndex = XrayImages.Num() - 1;

	// refactor: turha muuttuja
	if (!ImagesSet)
	{
		SetImageArray();
	}


	if (!InputEnabled || fabs(Value) < Epsilon)
	{
		return;
	}

	// next picture (value 1)
	if (fabs(Value - 1) < Epsilon)
	{
		if (CurrentPictureIndex == LastPictureIndex)
		{
			CurrentPictureIndex = 0;
		}
		else
		{
			CurrentPictureIndex++;
		}
	}
	// previous picture (value -1)
	else if (fabs(Value + 1) < Epsilon)
	{
		
		if (CurrentPictureIndex == 0)
		{
			CurrentPictureIndex = LastPictureIndex;
		}
		else
		{
			CurrentPictureIndex--;
		}
	}


	if (CurrentPictureIndex != KeyStitchIndex)
	{
		print("no key");
		ShowPicture(XrayImages[CurrentPictureIndex]);
	}
	else
	{
		print("key");
		ShowPicture(XrayKeyImages[CurrentPictureIndex]);
	}
	FTimerHandle TimerHandle;
	InputEnabled = false;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AComputer::TimerElapse, InputDelayInSeconds, false);
}

void AComputer::TimerElapse()
{
	InputEnabled = true;
}


void AComputer::ShowPicture_Implementation(UTexture2D* Texture)
{

}
