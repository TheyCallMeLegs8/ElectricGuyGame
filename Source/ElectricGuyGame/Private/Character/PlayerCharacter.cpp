// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MyPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, RotationSpeed, 0.f); // the rotation rate for here doesn't matter cause this is called when the editor starts. if there wasn't already a variable to tune this then I'm sure that putting this in begin play would work
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// creates camera and spring arm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Player SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::OnJump()
{
	Jump();
}

void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();
	//check(PlayerController);

	if (AMyPlayerController* PlayerController = GetController<AMyPlayerController>())
	{
		PlayerController->OnJumpInput.AddUObject(this, &APlayerCharacter::OnJump);
	}
	
	//PlayerController->OnJumpInput.AddUObject(this, &APlayerCharacter::OnJump);
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
