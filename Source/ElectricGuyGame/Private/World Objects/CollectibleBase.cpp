// Fill out your copyright notice in the Description page of Project Settings.


#include "World Objects/CollectibleBase.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ACollectibleBase::ACollectibleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleTrigger"));
	CapsuleCollider->SetGenerateOverlapEvents(true);
}

void ACollectibleBase::Collect(AActor* Collector)
{
}

// Called when the game starts or when spawned
void ACollectibleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

