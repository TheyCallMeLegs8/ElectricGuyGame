// Fill out your copyright notice in the Description page of Project Settings.


#include "World Objects/DashCrystal.h"

#include "Character/PlayerCharacter.h"

void ADashCrystal::Collect(AActor* Collector)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(Collector))
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("COLLECTED DASH CRYSTAL"));
		Player->ResetDashCooldown();
	}
}

// Sets default values
ADashCrystal::ADashCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADashCrystal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADashCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

