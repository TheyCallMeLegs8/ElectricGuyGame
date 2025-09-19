// Fill out your copyright notice in the Description page of Project Settings.


#include "World Objects/DashCrystal.h"

#include "Character/PlayerCharacter.h"


// Sets default values
ADashCrystal::ADashCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//CapsuleCollider = FindComponentByClass<UCapsuleComponent>();
}

// Called when the game starts or when spawned
void ADashCrystal::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &ADashCrystal::EndOverlap);
}

// Called every frame
void ADashCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADashCrystal::Collect(AActor* Collector)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("Collided"));
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(Collector))
	{
		CollidedPlayer = Player;

		if (!CollidedPlayer->GetCanDash())
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Blue, TEXT("PlayerCantDash"));
			RefreshPlayerDash();
		}
		else
		{
			CollidedPlayer->OnPlayerDash.AddDynamic(this, &ADashCrystal::RefreshPlayerDash);
			GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("Subscribed"));
		}
		
		//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("COLLECTED DASH CRYSTAL"));
		//CollidedPlayer->ResetDashCooldown();
	}
}

void ADashCrystal::RefreshPlayerDash()
{
	if (CollidedPlayer == nullptr) return;
	CollidedPlayer->ResetDashCooldown();
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Green, TEXT("DashRefreshed"));
}

void ADashCrystal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("Un-Collided"));
	if (OtherActor == CollidedPlayer)
	{
		CollidedPlayer->OnPlayerDash.RemoveAll(this);
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("Un-Subscribed"));
	}

	/*
	if (OtherActor->GetComponentByClass(APlayerCharacter::StaticClass()))
	{
		
	}*/
}
