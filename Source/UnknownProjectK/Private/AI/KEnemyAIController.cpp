// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/KEnemyAIController.h"
#include "AI/KEnemyAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/KAIPerceptionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIController, All, All)

AKEnemyAIController::AKEnemyAIController()
{
  KPerceptionComponent = CreateDefaultSubobject<UKAIPerceptionComponent>("PerceptionComponent");
  SetPerceptionComponent(*KPerceptionComponent);
}


void AKEnemyAIController::OnPossess(APawn *InPawn) {
  Super::OnPossess(InPawn);
  const auto EnemyCharacter = Cast<AKEnemyAICharacter>(InPawn);

  if (!EnemyCharacter) {
    return;
  }
  RunBehaviorTree(EnemyCharacter->BehaviorTreeAsset);
}
void AKEnemyAIController::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);

  const auto ActorFocus = GetFocusOnActor();
 // const auto ActorFocus = KPerceptionComponent->GetVisibleCharacter(); 
  int tmp = ActorFocus?1:0;
  UE_LOG(LogAIController, Warning, TEXT("AI %i"),tmp );
  SetFocus(ActorFocus);
}
AActor *AKEnemyAIController::GetFocusOnActor()
{
  if(GetBlackboardComponent())
  {
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKey));
  }
  return nullptr;
}