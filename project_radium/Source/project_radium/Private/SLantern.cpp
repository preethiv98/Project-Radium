// Fill out your copyright notice in the Description page of Project Settings.


#include "SLantern.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include "Kismet/GameplayStatics.h"
#include "project_radium/SCharacter.h"

// Sets default values
ASLantern::ASLantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;


}

// Called when the game starts or when spawned
void ASLantern::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASLantern::CastAttack()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);


		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);



		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility))
		{
			//Blocking hit! Process damage
			AActor* HitActor = Hit.GetActor();

			MyCharacter = Cast<ASCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			int wispCount = MyCharacter->wispsCount;


			UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);



		


		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
	}

	
}

// Called every frame
void ASLantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

