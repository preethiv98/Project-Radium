// Fill out your copyright notice in the Description page of Project Settings.


#include "WispsPickup.h"
#include "SCharacter.h"

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

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
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
			OtherActor->Destroy();

		}


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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}