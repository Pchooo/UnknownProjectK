// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseItem::ABaseItem() {
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	ItemMesh->SetupAttachment(GetRootComponent());
}
void ABaseItem::DoAction() {}
void ABaseItem::Drop() {}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}



