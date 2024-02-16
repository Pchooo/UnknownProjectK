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

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnSphereBeginOverlap);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionResponseToChannels(ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}


void ABaseItem::DoAction() {}


void ABaseItem::Drop()//TODO: need ref.
{
	UE_LOG(BaseItemLog, Warning, TEXT("Drop"));
	CollisionComponent->SetSimulatePhysics(true);
	
	CollisionComponent->SetCollisionResponseToChannels(ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetWorld()->GetTimerManager().SetTimer(EnableCollisionTimerHandle, this, &ABaseItem::EnableCollision, CollisionDelay, false);
}


void ABaseItem::EnableCollision() const//TODO: remove it when the button interaction is done
{
	UE_LOG(BaseItemLog, Warning, TEXT("Colllision ON"));
	
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned



void ABaseItem::OnSphereBeginOverlap(UPrimitiveComponent *OverlappedComponent,
                                     AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp,
                                     int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult &SweepResult)
{
        UE_LOG(BaseItemLog, Warning, TEXT("BaseItemOverlap"));
        if (!OtherActor)
          return;
        const auto Character = Cast<AUnknownProjectKCharacter>(OtherActor);

        if (!Character)
          return;

        CollisionComponent->SetSimulatePhysics(false);

        Character->AddItemToInventory(this);
        CollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
}

void ABaseItem::SetVisibility(bool VisibilityMode)
{
	if(ItemMesh)
	{
		ItemMesh->SetVisibility(VisibilityMode);
	}
}

