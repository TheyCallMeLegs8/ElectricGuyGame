// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Collectible.h"
#include "CollectibleBase.generated.h"

UCLASS(Abstract)

class ELECTRICGUYGAME_API ACollectibleBase : public AActor, public ICollectible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleBase();
	virtual void Collect(AActor* Collector) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox", BlueprintReadWrite)
	UCapsuleComponent* CapsuleCollider;
};
