// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AWispsPickup;
class ASLantern;

UCLASS()
class PROJECT_RADIUM_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Health;
	// Sets default values for this character's properties
	ASCharacter();

	UPROPERTY(BlueprintReadOnly, Category = "Wisps", meta = (ClampMin = 0))
		int wispsCount;


	float GetHoldTime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);

	void MoveRight(float Value);

	void OnPressed();

	void OnRelease();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Mesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Mesh2;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASLantern> lanternClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 3.0))
		float holdTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 6.0))
		float coolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool heldDown;


	ASLantern* lantern;
	

	UPROPERTY(BlueprintReadOnly, Category = "Player")
		bool bDied;

		bool bWantsToZoom;

		UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;

		UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 100))
		float ZoomInterpSpeed;

		

		float DefaultFOV;

		void BeginZoom();

		void EndZoom();

	

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;


};
