// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ELECTRICGUYGAME_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	

	
public:
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RotationSpeed = 400.0f;

	// camera components
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;
};
