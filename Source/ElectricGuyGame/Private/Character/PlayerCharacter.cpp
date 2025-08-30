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

	DashCooldown = 2.0f;
	CanDash = true;
	DashForce = 4400.f;
}

void APlayerCharacter::OnJump()
{
	Jump();
}

void APlayerCharacter::OnDash()
{
	if (!CanDash) return;
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("DASHED"));
			
	//UE::Math::TVector<double> LaunchVelocity = ControlledPawn->GetVelocity() * 10.f;
			
	LaunchCharacter(GetActorForwardVector() * DashForce, false, false);

	CanDash = false;
	//FTimerHandle DashTimerHandle;
	//TimerManager.SetTimer(DashTimerHandle, this, &APlayerCharacter::ResetDashCooldown, DashCooldown, false, -1);
	GetWorld()->GetTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::ResetDashCooldown, DashCooldown, false, -1);
}

void APlayerCharacter::ResetDashCooldown()
{
	CanDash = true;
}

void APlayerCharacter::OnMove(FVector2D InputAxisVector)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, InputAxisVector.Y);
	AddMovementInput(RightDirection, InputAxisVector.X);
}

void APlayerCharacter::OnLook(FVector2D InputVector)
{
	AddControllerYawInput(InputVector.X * XModifier);
	AddControllerPitchInput(InputVector.Y * YModifier);
}

void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();
	//check(PlayerController);
	
	if (AMyPlayerController* PlayerController = GetController<AMyPlayerController>())
	{
		PlayerController->OnJumpInput.AddUObject(this, &APlayerCharacter::OnJump);
		PlayerController->OnDashInput.AddUObject(this, &APlayerCharacter::OnDash);
		PlayerController->OnMoveInput.AddUObject(this, &APlayerCharacter::OnMove);
		PlayerController->OnLookInput.AddUObject(this, &APlayerCharacter::OnLook);
	}
	
	//PlayerController->OnJumpInput.AddUObject(this, &APlayerCharacter::OnJump);

	// inverts camera directions if needed
	if(InvertCamX) XModifier = -1;
	if(InvertCamY) YModifier = -1;

}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
