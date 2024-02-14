// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KInventoryComponent.h"
#include "Items/BaseItem.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/UnknownProjectKCharacter.h"
DEFINE_LOG_CATEGORY_STATIC(InventoryLog, All , All)

// Sets default values for this component's properties
UKInventoryComponent::UKInventoryComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = false;
  // ...
}

void UKInventoryComponent::SetupActionBindings()
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;
	

	const auto Controller = Cast<APlayerController>(Character->Controller);
	if(!Controller) return;
	
	const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Controller->GetLocalPlayer());
	if (!Subsystem) return;
	
	Subsystem->AddMappingContext(InventoryMappingContext, 1);

	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(Controller->InputComponent);
	if(!EnhancedInputComponent) return;

	EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Triggered, this, &UKInventoryComponent::DoAction);
	EnhancedInputComponent->BindAction(DropItemAction, ETriggerEvent::Triggered, this, &UKInventoryComponent::Drop);
	EnhancedInputComponent->BindAction(NextItemAction, ETriggerEvent::Triggered, this, &UKInventoryComponent::NextItem);
	EnhancedInputComponent->BindAction(PreviousItemAction, ETriggerEvent::Triggered, this, &UKInventoryComponent::PreviousItem);
}




void UKInventoryComponent::NextItem()
{
	UE_LOG(InventoryLog, Warning, TEXT("NextItem"));
}


void UKInventoryComponent::PreviousItem()
{
	UE_LOG(InventoryLog, Warning, TEXT("Prev item"));
}


void UKInventoryComponent::DoAction() 
{
	if(CurrentItem) {
		UE_LOG(InventoryLog, Warning, TEXT("DoAction"));
		CurrentItem->DoAction();
	}
}


void UKInventoryComponent::Drop()
{
	if(!CurrentItem) return;
	UE_LOG(InventoryLog, Warning, TEXT("DropItem"));
	if(Items.Remove(CurrentItem))
	{
		UE_LOG(InventoryLog, Warning, TEXT("pop"));
	}
	else
	{
		UE_LOG(InventoryLog, Warning, TEXT("cock"));
	}
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	CurrentItem->DetachFromActor(DetachmentRules);
	CurrentItem->Drop(); //TODO
	CurrentItem = nullptr;
	
}


void UKInventoryComponent::AddItem(ABaseItem *Item)
{
	const auto Character = Cast<AUnknownProjectKCharacter>(GetOwner());
	if(!GetWorld() || !Character ) return;

	
	
	//TODO: checking for the existence of the same object in the inventory
	Item->SetOwner(Character);
	Items.Add(Item);
	if(!CurrentItem) CurrentItem = Item; //TODO: temporary. Player should equip
	
	AttachItemToSocket(Item, Character->GetMesh1P());
	return;
}

// Called when the game starts
void UKInventoryComponent::BeginPlay() {
        Super::BeginPlay();
	SetupActionBindings();
        // ...
}
void UKInventoryComponent::SpawnItems() {}


void UKInventoryComponent::AttachItemToSocket(ABaseItem *Item, USkeletalMeshComponent *SkeletalMeshComponent) const
{
        if (!Item || !SkeletalMeshComponent) return;
	
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,true);
        Item->AttachToComponent(SkeletalMeshComponent, AttachmentRules,
                                ItemEquipSocketName);
}





