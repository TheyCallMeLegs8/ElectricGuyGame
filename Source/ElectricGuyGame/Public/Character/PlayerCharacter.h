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

	//Dash variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Components")
	bool CanDash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Components")
	float DashCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash Components")
	float DashForce;
	
	//FTimerManager& TimerManager = GetWorldTimerManager();
	FTimerHandle DashCooldownTimer;

	
	// Camera Inverting Modifiers
	UPROPERTY(EditAnywhere, Category = "Camera Modifiers", BlueprintReadWrite)
	bool InvertCamX = false;
	UPROPERTY(EditAnywhere, Category = "Camera Modifiers", BlueprintReadWrite)
	bool InvertCamY = false;
	int XModifier = 1;
	int YModifier = 1;


	UPROPERTY(EditAnywhere, Category = "Capsule", BlueprintReadWrite)
	UCapsuleComponent* CapsuleCollider;
	
	// trigger collider variables
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TriggerBox")
	UCapsuleComponent* CapsuleCollider;
	*/
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	//UPROPERTY(EditAnywhere)
	//AMyPlayerController* PlayerController = GetController<AMyPlayerController>();
	//= UGameplayStatics::GetPlayerController(this, 0)
public:
	APlayerCharacter();
	
	UFUNCTION()
	void OnJump();
	UFUNCTION()
	void OnDash();
	UFUNCTION()
	void OnMove(FVector2D InputAxisVector);
	UFUNCTION()
	void OnLook(FVector2D InputVector);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RotationSpeed = 400.0f;

	// HEY
	// WE TURN THIS INTO AN EVENT
	// HEY
	UFUNCTION()
	void ResetDashCooldown();
	
	// camera components
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;
};
