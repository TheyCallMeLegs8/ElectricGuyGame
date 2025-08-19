// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyCustomEvent, int32, Value);

/**
 * 
 */
UCLASS()
class ELECTRICGUYGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

	//UPROPERTY(BlueprintAssignable, Category = "Events")
	//FMyCustomEvent OnMyCustomEvent;

	DECLARE_MULTICAST_DELEGATE(FOnJumpInput);
	FOnJumpInput OnJumpInput;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PlayerSpringArm;

	UPROPERTY(EditAnywhere, Category = "Camera Modifiers", BlueprintReadWrite)
	bool InvertCamX = false;
	UPROPERTY(EditAnywhere, Category = "Camera Modifiers", BlueprintReadWrite)
	bool InvertCamY = false;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DashAction;

	// Camera Inverting Modifiers
	int XModifier = 1;
	int YModifier = 1;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void Dash(const FInputActionValue& InputActionValue);
};
