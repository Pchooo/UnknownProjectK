// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"

// Sets default values
ABaseItem::ABaseItem() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
}
void ABaseItem::DoAction() {}
void ABaseItem::Drop() {}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame


