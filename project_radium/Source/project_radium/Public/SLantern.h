// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SLantern.generated.h"



class ASCharacter;
class USkeletalMeshComponent;
class UDamageType;

class UAudioComponent;


UCLASS()
class PROJECT_RADIUM_API ASLantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLantern();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 3.0))
		float holdTime;

	UFUNCTION(BlueprintCallable)
	float GetCooldown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool heldDown;

	

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual	void CastAttack();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 6.0))
		float coolDown;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASCharacter> CharacterClass;


	ASCharacter* MyCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
