#pragma once

#include "FocusableActor.h"
#include "Patient.generated.h"




UCLASS()
class CROWMIRE_API APatient : public AUsableActor
{
	GENERATED_BODY()

public:
	APatient();
	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = Puzzle)
	uint8 GetKeyStitchIndex();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
		void OnStitchSelected(bool WasCorrect);
	void OnStitchSelected_Implementation(bool WasCorrect);

	void SetKeyStitchIndex(uint8 KeyStitchIndex);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* StitchSceneComponent;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stitch)
		UStaticMeshComponent* Hip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stitch)
		UStaticMeshComponent* RightArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stitch)
		UStaticMeshComponent* LeftArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stitch)
		UStaticMeshComponent* Chest;

	TMap<FString, UStaticMeshComponent**> Stitches;



	

private:
	uint8 KeyStitchIndex;
};
