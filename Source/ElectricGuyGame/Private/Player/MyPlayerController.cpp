// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "Runtime/AIModule/Classes/Actions/PawnAction_Move.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);

	// Shows mouse cursor and sets its skin to Default
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Allows mouse to interact with UI
	FInputModeGameAndUI InputModeData;
	FInputModeGameOnly InputModeGameOnly;
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//InputModeData.SetHideCursorDuringCapture(false); 	// Doesn't hide mouse when it enters viewport

	//SetInputMode(InputModeData);
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);
	
	
	// reference to camera
	PlayerCamera = GetPawn<APawn>()->GetComponentByClass<UCameraComponent>();
	PlayerSpringArm = GetPawn<APawn>()->GetComponentByClass<USpringArmComponent>();
	//PlayerCamera->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(100.0f, 500.0f, 20.0f), FVector(1.0f, 1.0f, 1.0f)));
	
	if(InvertCamX)
	{
		XModifier = -1;
	}
	if(InvertCamY)
	{
		YModifier = -1;
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Dash);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping); 
}

void AMyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AMyPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X * XModifier);
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y * YModifier);
		//PlayerSpringArm->AddLocalRotation(FRotator(InputAxisVector.Y, InputAxisVector.X, 0.f));
	}
}

void AMyPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (JumpAction)
	{
		if (ACharacter* ControlledPawn = GetPawn<ACharacter>()) 
		{
			ControlledPawn->Jump();

			//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("JUMP"));
			
			/*
			if (ACharacter* PlayerController = ControlledPawn->GetController<ACharacter>())
			{
				GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("JUMP!")); 
			
				PlayerController->Jump();
			}*/
		}
	}
}

void AMyPlayerController::Dash(const FInputActionValue& InputActionValue)
{
	if (DashAction)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("DETECTED INPUT"));

		if (ACharacter* ControlledPawn = GetPawn<ACharacter>()) 
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("DASHED"));
			
			//UE::Math::TVector<double> LaunchVelocity = ControlledPawn->GetVelocity() * 10.f;
			
			ControlledPawn->LaunchCharacter(ControlledPawn->GetActorForwardVector() * 4400.f, false, false);
		}
	}
}

/*
void AMyPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if (float FloatValue = InputActionValue.Get<float>())
	{
		float temp = PlayerSpringArm->GetRelativeRotation().Pitch + FloatValue;
		if (temp < 25 && temp > -65)
		{
			PlayerSpringArm->AddLocalRotation(FRotator(FloatValue, 0.f, 0.f));
		}
	}

	if (float FloatValue = InputActionValue.Get<float>())
	{
		float temp = PlayerSpringArm->GetRelativeRotation().Yaw + FloatValue;
		if (temp < 25 && temp > -65)
		{
			PlayerSpringArm->AddLocalRotation(FRotator(0.f, FloatValue, 0.f));
		}
	}
}


void AMyPlayerController::Look(float& InputActionValue)
{
	if (InputActionValue)
	{
		float temp = PlayerSpringArm->GetRelativeRotation().Pitch + InputActionValue;
		if (temp < 25 && temp > -65)
		{
			PlayerSpringArm->AddLocalRotation(FRotator(InputActionValue, 0.f, 0.f));
		}
	}
}

void AMyPlayerController::Look(const FInputActionValue& InputActionValue)
{

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		PlayerSpringArm->AddLocalRotation(FRotator(InputAxisVector.Y, InputAxisVector.X, 0.f));
	}
}
*/
