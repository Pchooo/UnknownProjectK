// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KInventoryComponent.h"
#include "Items/BaseItem.h"
#include "GameFramework/Character.h"
// Sets default values for this component's properties
UKInventoryComponent::UKInventoryComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = false;

  // ...
}
void UKInventoryComponent::NextItem() const {}


void UKInventoryComponent::PreviousItem() const
{}


void UKInventoryComponent::DoAction() const
{
	if(CurrentItem) {
		CurrentItem->DoAction();
	}
}


void UKInventoryComponent::Drop() {}
void UKInventoryComponent::AddItem(ABaseItem *Item)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!GetWorld() || !Character ) return;
	//TODO: checking for the existence of the same object in the inventory
	Item->SetOwner(Character);
	Items.Add(Item);
	AttachItemToSocket(Item, Character->GetMesh());
	
	
}

// Called when the game starts
void UKInventoryComponent::BeginPlay() {
        Super::BeginPlay();

        // ...
}
void UKInventoryComponent::SpawnItems() {}

void UKInventoryComponent::AttachItemToSocket(ABaseItem *Item,
                                              USceneComponent *SceneComponent) const
{
	if(!Item || !SceneComponent) return; 
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Item->AttachToComponent(SceneComponent, AttachmentRules, ItemEquipSocketName);
}



