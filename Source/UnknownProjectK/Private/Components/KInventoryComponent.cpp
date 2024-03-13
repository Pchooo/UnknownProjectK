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


void UKInventoryComponent::BeginPlay() {
	Super::BeginPlay();
	SetupActionBindings();
	
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
	if (Items.Num() < 1) return;
	
	CurrentItemIndex = (CurrentItemIndex + 1) % Items.Num();
	UE_LOG(InventoryLog, Warning, TEXT("NextItem ind %d %d"), CurrentItemIndex, Items.Num() );
	SetCurrentItem(Items[CurrentItemIndex]);
}


void UKInventoryComponent::PreviousItem()
{
	if (Items.Num() < 1) return;

	CurrentItemIndex = CurrentItemIndex > 0 ? (CurrentItemIndex - 1) % Items.Num() : Items.Num() - 1;
	UE_LOG(InventoryLog, Warning, TEXT("Prev item ind %d  %d"), CurrentItemIndex,  Items.Num());
	SetCurrentItem(Items[CurrentItemIndex]);
}


void UKInventoryComponent::DoAction()
{
	if(CurrentItem)
	{
		UE_LOG(InventoryLog, Warning, TEXT("DoAction"));
		CurrentItem->DoAction();
	}
}


void UKInventoryComponent::Drop()//TODO перенести функцию дропа снизу вверх и с лог значением (чтоб некоторые обекты нельзя было дропать)
{
	if(!CurrentItem) return;
	UE_LOG(InventoryLog, Warning, TEXT("DropItem. Cur item ind %d  %d"), CurrentItemIndex,  Items.Num());

	Items.Remove(CurrentItem);
	
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	CurrentItem->DetachFromActor(DetachmentRules);
	CurrentItem->Drop(); //TODO
	CurrentItem = nullptr;
	CurrentItemIndex--;
	
	PreviousItem();
}


void UKInventoryComponent::AddItem(ABaseItem *Item) {
        const auto Character = Cast<AUnknownProjectKCharacter>(GetOwner());
	
        if (!GetWorld() || !Character)
                return;
        if (Items.Num() > MaxNumberItems)
                return;

        // TODO: checking for the existence of the same object in the inventory
        Item->SetOwner(Character);
        Items.Add(Item);

        if (!CurrentItem)
        {
        	CurrentItem = Item; // TODO: temporary. Player should equip;
        	CurrentItemIndex = 0;
        }
	else
	{
		Item->SetVisibility(false);
        }
        AttachItemToSocket(Item, Character->GetMesh1P());
	//AttachItemToSocket(Item, Character->GetMesh());
      
}

void UKInventoryComponent::SetCurrentItem(ABaseItem* NewCurrentItem)
{
	if(CurrentItem)
	{
		CurrentItem->SetVisibility(false);
	}
	CurrentItem = NewCurrentItem;
	NewCurrentItem->SetVisibility(true);
}


void UKInventoryComponent::SpawnItems() {}


void UKInventoryComponent::AttachItemToSocket(ABaseItem *Item, USkeletalMeshComponent *SkeletalMeshComponent) const
{
        if (!Item || !SkeletalMeshComponent) return;
	
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,true);
        Item->AttachToComponent(SkeletalMeshComponent, AttachmentRules,
                                ItemEquipSocketName);
}





