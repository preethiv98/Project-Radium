// Fill out your copyright notice in the Description page of Project Settings.


#include "SLantern.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "project_radium/SCharacter.h"

// Sets default values
ASLantern::ASLantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;


	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Lantern"));
	audioComponent->SetupAttachment(RootComponent);

	

}

float ASLantern::GetCooldown()
{
	return coolDown;
}

// Called when the game starts or when spawned
void ASLantern::BeginPlay()
{
	Super::BeginPlay();
	// Get world.
	//UWorld* World = this->GetWorld();
	//if (World)
	//{
	//	// Spawn params.
	//	FActorSpawnParameters Spawn_Parameters;
	//	Spawn_Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//	// Spawn.
	//	MyCharacter = World->SpawnActor<ASCharacter>(CharacterClass, Spawn_Parameters);
	//}
}

void ASLantern::CastAttack()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		float chargeTime = 0.0f;
		MyCharacter = Cast<ASCharacter>(MyOwner);		

		if (MyCharacter)
		{
		 chargeTime = MyCharacter->GetHoldTime();
		}
	

		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);
		FVector ShotDirection = EyeRotation.Vector();

		if (chargeTime < 1)
		{
			if (MyCharacter->wispsCount >= 1)
			{
				TraceEnd = EyeLocation + (EyeRotation.Vector() * 1000);
				coolDown = 4.0f;
				
			}

		}

		if (chargeTime >= 1 && chargeTime <= 2)
		{
			if (MyCharacter->wispsCount >= 2)
			{
			TraceEnd = EyeLocation + (EyeRotation.Vector() * 2000);
			coolDown = 6.0f;
		
			}
		}

		if (chargeTime > 2)
		{
			if (MyCharacter->wispsCount >= 3)
			{
			TraceEnd = EyeLocation + (EyeRotation.Vector() * 3000);
			coolDown = 8.0f;
			
			}
		}


		FString debugC = FString::SanitizeFloat(coolDown);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *debugC);
		}

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility))
		{
			//Blocking hit! Process damage
			AActor* HitActor = Hit.GetActor();
			
			if (MuzzleEffect)
			{
				UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp,"Muzzle");
			}
			

			if (audioComponent && Impact)
			{
				audioComponent->SetSound((USoundBase*)Impact);
				audioComponent->Play(0.5f);
			}

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

