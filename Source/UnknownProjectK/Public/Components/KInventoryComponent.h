// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KInventoryComponent.generated.h"

class ABaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNPROJECTK_API UKInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKInventoryComponent();
	void NextItem() const;
	void PreviousItem() const;
	void DoAction() const;
	void Drop();
	void AddItem(ABaseItem* Item);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//TODO: ENDPLAY
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item", meta=(ClampMin = 1, ClampMax = 10))
	int32 MaxNumberItems = 6;

	UPROPERTY()
	TArray<TSubclassOf<ABaseItem>> DefaultItems;//for default items. may be removed

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TArray<ABaseItem*> Items;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	FName ItemEquipSocketName = "GripPoint";
private:
	UPROPERTY()
	ABaseItem* CurrentItem = nullptr;

	int32 CurrentItemIndex = 0;
	
	//TODO: SPAWN
	void SpawnItems(); //for default items. Not used for now

	void AttachItemToSocket(ABaseItem* Item, USceneComponent* SceneComponent) const;
};
