// Fill out your copyright notice in the Description page of Project Settings.
#include "SCharacter.h"
#include "SLantern.h"
#include "Components/AudioComponent.h"
#include "WispsPickup.h"



// Sets default values
ASCharacter::ASCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);


	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 1"));
	Mesh1->SetupAttachment(RootComponent);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASCharacter::OnOverlapBegin);
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 2"));
	Mesh2->SetupAttachment(RootComponent);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Lantern"));
	audioComponent->SetupAttachment(RootComponent);


	ZoomedFOV = 65.0f;
	ZoomInterpSpeed = 20.0f;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = CameraComp->FieldOfView;
	
	//Spawn a default Weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//HealthComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);

	lantern = GetWorld()->SpawnActor<ASLantern>(lanternClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (lantern)
	{
		lantern->SetOwner(this);
		lantern->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Lantern");
	}

}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
	if (audioComponent && Movement)
	{
		audioComponent->SetSound((USoundBase*)Movement);
		audioComponent->Play(0.5f);
	}
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
	if (audioComponent && Movement)
	{
		audioComponent->SetSound((USoundBase*)Movement);
		audioComponent->Play(0.5f);
	}
}


void ASCharacter::BeginZoom()
{
	bWantsToZoom = true;
}


void ASCharacter::EndZoom()
{
	bWantsToZoom = false;
}


float ASCharacter::GetHoldTime()
{
	return holdTime;
}

void ASCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (OtherActor->IsA(AWispsPickup::StaticClass()))
		{
			/*APickup* pickup = Cast<APickup>(OtherActor);
			if (pickup)
			{
				UItem* it = pickup->GetItem();
				if (it)
				{
					Inventory->AddItem(it);
				}
			}*/
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pick Me UP!!!"));
			}
			wispsCount++;
			//OtherActor->Destroy();

		}
	

	}
}


void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(NewFOV);

	if (heldDown)
	{
		holdTime = GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	}
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASCharacter::OnPressed);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ASCharacter::OnRelease);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);

}

void ASCharacter::OnPressed()
{
	heldDown = true;
	if (audioComponent && LanternCharge && wispsCount != 0)
	{
		audioComponent->SetSound((USoundBase*)LanternCharge);
		audioComponent->Play(0.5f);
	}
	else if(audioComponent)
	{
		audioComponent->SetSound((USoundBase*)LanternFailed);
		audioComponent->Play(0.5f);
	}
}

void ASCharacter::SetWispsCount(int wispCount)
{
	wispsCount = wispCount;
}

void ASCharacter::OnRelease()
{
	heldDown = false;
	FString debugC = FString::SanitizeFloat(holdTime);
	if (lantern && wispsCount != 0)
	{
		lantern->SetOwner(this);
		lantern->CastAttack();
		if (audioComponent && LanternFire)
		{
			audioComponent->SetSound((USoundBase*)LanternFire);
			audioComponent->Play(0.5f);
		}

		if (holdTime < 1)
		{
			wispsCount--;
		}

		if (holdTime >= 1 && holdTime <= 2)
		{
			if (wispsCount >= 2)
			{
			wispsCount -= 2;
			}
			
		}

		if (holdTime > 2)
		{
			if (wispsCount >= 3)
			{
				wispsCount -= 3;
			}
		}
	}




	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *debugC);
	}
}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}