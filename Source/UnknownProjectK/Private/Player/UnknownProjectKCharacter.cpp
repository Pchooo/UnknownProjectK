// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/UnknownProjectKCharacter.h"
#include "Animation/AnimInstance.h"
#include "BaseItem.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/KInventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UnknownProjectKProjectile.h"

#include <complex.h>

DEFINE_LOG_CATEGORY_STATIC(LogCharacter, All, All)

AUnknownProjectKCharacter::AUnknownProjectKCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Inventory component
	InventoryComponent = CreateDefaultSubobject<UKInventoryComponent>("InventoryComponent");
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AUnknownProjectKCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	

}

//////////////////////////////////////////////////////////////////////////// Input

void AUnknownProjectKCharacter::SetupPlayerInputComponent(
    class UInputComponent *PlayerInputComponent) {
        // Set up action bindings
        if (UEnhancedInputComponent *EnhancedInputComponent =
                CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
                // Jumping
                EnhancedInputComponent->BindAction(JumpAction,
                                                   ETriggerEvent::Triggered,
                                                   this, &ACharacter::Jump);
                EnhancedInputComponent->BindAction(
                    JumpAction, ETriggerEvent::Completed, this,
                    &ACharacter::StopJumping);

                // Moving
                EnhancedInputComponent->BindAction(
                    MoveAction, ETriggerEvent::Triggered, this,
                    &AUnknownProjectKCharacter::Move);

                // Looking
                EnhancedInputComponent->BindAction(
                    LookAction, ETriggerEvent::Triggered, this,
                    &AUnknownProjectKCharacter::Look);
        }
}


void AUnknownProjectKCharacter::AddItemToInventory(ABaseItem *Item)
{
	UE_LOG(LogCharacter, Warning, TEXT("Add item char"))
	InventoryComponent->AddItem(Item);
}

void AUnknownProjectKCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUnknownProjectKCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUnknownProjectKCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AUnknownProjectKCharacter::GetHasRifle()
{
	return bHasRifle;
}