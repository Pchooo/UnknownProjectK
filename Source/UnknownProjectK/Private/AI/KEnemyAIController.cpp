// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/KEnemyAIController.h"
#include "AI/KEnemyAICharacter.h"


void AKEnemyAIController::OnPossess(APawn *InPawn)
{
  Super::OnPossess(InPawn);
  const auto EnemyCharacter = Cast<AKEnemyAICharacter>(InPawn);

  if(!EnemyCharacter) {
    return;
  }
  RunBehaviorTree(EnemyCharacter->BehaviorTreeAsset);
}