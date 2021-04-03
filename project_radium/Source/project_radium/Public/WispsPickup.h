// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WispsPickup.generated.h"

class UBoxComponent;


UCLASS()
class PROJECT_RADIUM_API AWispsPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWispsPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		FRotator RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxCollider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
