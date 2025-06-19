// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include <EnhancedInputSubsystems.h>

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
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false); 	// Doesn't hide mouse when it enters viewport

	SetInputMode(InputModeData);
}
