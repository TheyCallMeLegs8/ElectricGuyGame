// Fill out your copyright notice in the Description page of Project Settings.


#include "World Objects/DashWire.h"

#include "Components/SplineComponent.h"

// Sets default values
ADashWire::ADashWire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("MySpline"));
	Spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADashWire::BeginPlay()
{
	Super::BeginPlay();

	if (SplineMesh != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::White, TEXT("Spline Mesh Not Null"));
	}
}

// Called every frame
void ADashWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

