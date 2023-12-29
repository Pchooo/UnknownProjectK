// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KInventoryComponent.h"
#include "Items/BaseItem.h"
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


void UKInventoryComponent::DoAction() const {
	if(CurrentItem) {
		CurrentItem->DoAction();
	}
}


void UKInventoryComponent::Drop(){}

// Called when the game starts
void UKInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



