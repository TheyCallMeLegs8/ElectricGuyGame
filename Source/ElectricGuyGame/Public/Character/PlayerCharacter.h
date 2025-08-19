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

	//UPROPERTY(EditAnywhere)
	//AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
	//= UGameplayStatics::GetPlayerController(this, 0)
public:
	APlayerCharacter();
	
	UFUNCTION()
	void OnJump();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RotationSpeed = 400.0f;

	// camera components
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;
};
