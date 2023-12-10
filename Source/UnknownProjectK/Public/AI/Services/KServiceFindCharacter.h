// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KServiceFindCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWNPROJECTK_API UKServiceFindCharacter : public UBTService
{
  GENERATED_BODY()
public:
  UKServiceFindCharacter();

protected:
  virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FBlackboardKeySelector EnemyActorKey;
};
