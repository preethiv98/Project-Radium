// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLantern.generated.h"

class ASCharacter;
class USkeletalMeshComponent;
class UDamageType;

UCLASS()
class PROJECT_RADIUM_API ASLantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLantern();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 3.0))
	float holdTime;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 6.0))
	float coolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void CastAttack();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	ASCharacter* MyCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
