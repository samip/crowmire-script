// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Inventory.h"
#include "crowmireCharacter.generated.h"


class UInputComponent;
class AUsableActor;
class APickableActor;
class AHudTextActor;

UCLASS(config=Game)
class AcrowmireCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	AcrowmireCharacter();

	void BeginPlay();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Raycast)
	FHitResult Rayhit;

	void GetUsableActor(FHitResult* Hit, FCollisionQueryParams* Params);

	UFUNCTION(BlueprintCallable, Category = HUdActor)
		void UpdateHudPosition(FVector Start, FVector Direction, FRotator CamRot);

	UFUNCTION(BlueprintCallable, Category = HUdActor)
		void ShowHudInfo(FString text);

	UFUNCTION(BlueprintCallable, Category = HUdActor)
		void HideHudInfo();

	virtual void Tick(float DeltaSeconds) override;

	/*
	Expose inventory methods for easier use in blueprints
	*/
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void AddItem(APickableActor* Item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		TArray<APickableActor*> GetInventoryItems();

	UFUNCTION(BlueprintCallable, Category = Inventory)
		bool HasItem(APickableActor* Item);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void SetItems(TArray<APickableActor*> Items);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void Remove(APickableActor* Item);

protected:
	UInputComponent* Input;

	AHudTextActor* HudActor;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	

	void Use();

	void ShowInventory();

	Inventory Inventory;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};
