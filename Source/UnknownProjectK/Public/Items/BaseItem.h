// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class UNKNOWNPROJECTK_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
	virtual void DoAction();
	virtual void Drop();
	//virtual void PickUpItem();
	
	void SetVisibility(bool VisibilityMode); 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, Category="Component")
	USphereComponent* CollisionComponent;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	

private:
	bool IsInInventory = false;
	FTimerHandle EnableCollisionTimerHandle; //TODO: remove it when the button interaction is done
	int32 CollisionDelay = 5;

	void EnableCollision() const; 
};
