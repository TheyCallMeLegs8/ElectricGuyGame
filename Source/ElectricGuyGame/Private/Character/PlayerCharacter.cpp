// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Collectible.h"
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
	CanResetDash = false;
	
	CapsuleCollider = GetCapsuleComponent();
	SetRootComponent(CapsuleCollider);
	CapsuleCollider->SetGenerateOverlapEvents(true);

	//WireDashCheckRadius = 5.0f;


	WireDashCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Wire Dash"));
	WireDashCollider->SetupAttachment(RootComponent);
	//WireDashCollider->CreateDefaultSubobject<UCapsuleComponent>(TEXT("Dash Wire Collider"));
	//WireDashCollider->SetupAttachment(CapsuleCollider);
	//WireDashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//WireDashCollider->SetGenerateOverlapEvents(true);
	//WireDashCollider->SetSphereRadius(WireDashCheckRadius);
	
	MovementComponent = GetCharacterMovement();
}


void APlayerCharacter::OnJump()
{
	Jump();
}

void APlayerCharacter::OnDash()
{/*
	if (!CanDash) return
			
	LaunchCharacter(GetActorForwardVector() * DashForce, false, false);
	OnPlayerDash.Broadcast();

	CanDash = false;
	CanResetDash = false;
	GetWorld()->GetTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::CheckIfResetDashIsViable, DashCooldown, false, -1);
	*/
	if (!CanDash) return;
			
	LaunchCharacter(GetActorForwardVector() * DashForce, false, false);

	CanDash = false;
	CanResetDash = false;
	GetWorld()->GetTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::CheckIfResetDashIsViable, DashCooldown, false, -1);
	OnPlayerDash.Broadcast();
}

void APlayerCharacter::CheckIfResetDashIsViable()
{
	//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("DASH TRY Reset"));
	GetWorldTimerManager().ClearTimer(DashCooldownTimer);
	CanResetDash = true;
	if (MovementComponent->IsWalking())
	{
		ResetDashCooldown();
		//return true;
	}
	else
	{
		//CanDash = false;
		//return false;
	}
}

void APlayerCharacter::ResetDashCooldown()
{
	CanDash = true;
	GetWorldTimerManager().ClearTimer(DashCooldownTimer);
}

bool APlayerCharacter::GetCanDash()
{
	return CanDash;
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	//GetWorldTimerManager().ClearTimer(DashCooldownTimer);
	if (CanResetDash)
	{
		ResetDashCooldown();
	}
	//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("Landed!!"));
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

void APlayerCharacter::OnWireDash()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, TEXT("WireDash"));
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
		PlayerController->OnWireDashInput.AddUObject(this, &APlayerCharacter::OnWireDash);
	}
	
	//PlayerController->OnJumpInput.AddUObject(this, &APlayerCharacter::OnJump);

	// inverts camera directions if needed
	if(InvertCamX) XModifier = -1;
	if(InvertCamY) YModifier = -1;

	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);
	//WireDashCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::WireDashCollideCheck);
	//CapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlap);
}

void APlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("TOUCHING"));
	//APlayerCharacter* Player = Cast<APlayerCharacter>(Collector)
	if (OtherActor->GetClass()->ImplementsInterface(UCollectible::StaticClass()))
	{
		ICollectible* CollidedCollectable = Cast<ICollectible>(OtherActor);
		CollidedCollectable->Collect(this);
		//GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Yellow, TEXT("Dashshhsh"));
	}
}

/*
void APlayerCharacter::WireDashCollideCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EnableWireDashCollider();
}*/

void APlayerCharacter::EnableWireDashCollider()
{
	WireDashCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APlayerCharacter::DisableWireDashCollider()
{
	WireDashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
