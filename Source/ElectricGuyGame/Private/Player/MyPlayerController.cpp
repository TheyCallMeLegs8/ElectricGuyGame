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
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Dash);
	EnhancedInputComponent->BindAction(WireDashAction, ETriggerEvent::Triggered, this, &AMyPlayerController::WireDash);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping); 
}

void AMyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	OnMoveInput.Broadcast(InputAxisVector);
}

void AMyPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	OnLookInput.Broadcast(InputAxisVector);

	/*
	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X * XModifier);
		ControlledPawn->AddControllerPitchInput(InputAxisVector.Y * YModifier);
		//PlayerSpringArm->AddLocalRotation(FRotator(InputAxisVector.Y, InputAxisVector.X, 0.f));
	}*/
}

void AMyPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (JumpAction)
	{
		OnJumpInput.Broadcast();
		//if (ACharacter* PlayerController = ControlledPawn->GetController<ACharacter>())
	}
}

void AMyPlayerController::Dash(const FInputActionValue& InputActionValue)
{
	if (DashAction)
	{
		//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("DETECTED INPUT"));

		OnDashInput.Broadcast();

		/*
		if (ACharacter* ControlledPawn = GetPawn<ACharacter>()) 
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("DASHED"));
			
			//UE::Math::TVector<double> LaunchVelocity = ControlledPawn->GetVelocity() * 10.f;
			
			ControlledPawn->LaunchCharacter(ControlledPawn->GetActorForwardVector() * 4400.f, false, false);
		}*/
	}
}

void AMyPlayerController::WireDash(const FInputActionValue& InputActionValue)
{
	if (WireDashAction)
	{
		//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("FIRST PHASE WIRE DASH"));
		OnWireDashInput.Broadcast();
	}
}
