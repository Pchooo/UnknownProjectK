// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/UnknownProjectKCharacter.h"
DECLARE_LOG_CATEGORY_CLASS(BaseItemLog, All, All)

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
        CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnSphereBeginOverlap);
}


void ABaseItem::OnSphereBeginOverlap(UPrimitiveComponent *OverlappedComponent,
                                     AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp,
                                     int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult &SweepResult)
{
        UE_LOG(BaseItemLog, Warning, TEXT("BaseItemOverlap"));
	if(!OtherActor) return;
	const auto Character = Cast<AUnknownProjectKCharacter>(OtherActor);
	
	if(!Character) return;
	UE_LOG(BaseItemLog, Warning, TEXT("Bbb"));
	Character->AddItemToInventory(this);
	CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
	
}

