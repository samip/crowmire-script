

#pragma once

#include "FocusableActor.h"
#include "Patient.h"
#include "Computer.generated.h"

/**
 * 
 */
UCLASS()
class CROWMIRE_API AComputer : public AFocusableActor
{
	GENERATED_BODY()
	
public:
	AComputer();
	void SetupInput() override;

	void BeginPlay();

	UFUNCTION(BlueprintNativeEvent, Category = Interaction)
		void ShowPicture(UTexture2D* Texture);
	void ShowPicture_Implementation(UTexture2D* Texture);

	UPROPERTY(BlueprintReadOnly)
		TArray<UTexture2D*> XrayImages;

	UPROPERTY(BlueprintReadOnly)
		TArray<UTexture2D*> XrayKeyImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InputDelayInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APatient* TargetPatient;

private:
	void SetImageArray();

	uint8 CurrentPictureIndex;
	uint8 KeyStitchIndex;

	void Browse(float Value);
	void TimerElapse();

	bool InputEnabled;
	bool ImagesSet;


	
};
