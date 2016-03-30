

#pragma once

#include "FocusableActor.h"
#include "Patient.h"
#include "Computer.generated.h"

/**
 * Logic for computer used for browsing xray pictures in zone 2 puzzle
 */
UCLASS()
class CROWMIRE_API AComputer : public AFocusableActor
{
	GENERATED_BODY()
	
public:
	AComputer();

	/*
	Called from character controller. Changes active camera to the one attached to this actor.
	*/
	void SetupInput() override;

	void BeginPlay();

	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void ShowPicture(UTexture2D* Texture);
	void ShowPicture_Implementation(UTexture2D* Texture);

	/* 
	Xray pictures without key
	*/
	UPROPERTY(BlueprintReadOnly)
		TArray<UTexture2D*> XrayImages;

	/* 
	Xray pictures with key
	*/
	UPROPERTY(BlueprintReadOnly)
		TArray<UTexture2D*> XrayKeyImages;

	/*
	Delay between registered key presses 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InputDelayInSeconds;
	
	/* 
	Reference to patient, needed to find key stitch index
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APatient* TargetPatient;

private:
	/*
	Build XrayImages and XrayKeyImages
	*/
	void InitializePictureArray();

	/* Current index in XrayImages */
	uint8 CurrentPictureIndex;
	
	/* 
	Index of the key picture. 
	If this equals CurrentKeyPictureIndex show picture from XrayKeyImages instead of XrayImages.
	*/
	uint8 KeyStitchIndex;

	/*
	Go to next/previous picture when player tries to "strafe" right/left
	*/
	void Browse(float Value);

	/*
	Input delay timer callback
	*/
	void TimerElapse();

	/* 
	Set false when input delay is active 
	*/
	bool InputEnabled;

};
