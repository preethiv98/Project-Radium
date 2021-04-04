// Fill out your copyright notice in the Description page of Project Settings.

#include "WispsPickup.h"
#include "Components/BoxComponent.h"


// Sets default values
AWispsPickup::AWispsPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);



	RotationRate = FRotator(0.0f, 180.0f, 0.0f);


	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AWispsPickup::OnOverlapBegin);
	BoxCollider->SetupAttachment(RootComponent);

}

void AWispsPickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

