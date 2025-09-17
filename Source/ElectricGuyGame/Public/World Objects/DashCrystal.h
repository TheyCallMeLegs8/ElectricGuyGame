// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectibleBase.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Collectible.h"
#include "DashCrystal.generated.h"

UCLASS()
class ELECTRICGUYGAME_API ADashCrystal : public ACollectibleBase
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ADashCrystal();
	virtual void Collect(AActor* Collector) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, Category = "Capsule", BlueprintReadWrite)
	//UCapsuleComponent* CapsuleCollider;
	
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere)
	APlayerCharacter* CollidedPlayer;
	UFUNCTION()
	void RefreshPlayerDash();
	
	//UPROPERTY(EditAnywhere, Category = "Capsule", BlueprintReadWrite)
	//UCapsuleComponent* CapsuleCollider;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
