// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KServiceFindCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/KAIPerceptionComponent.h"

UKServiceFindCharacter::UKServiceFindCharacter()
{
  NodeName = "FindCharacter";
}
void UKServiceFindCharacter::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
  const auto Blackboard = OwnerComp.GetBlackboardComponent();
  if(Blackboard) {
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller) {
      const auto PerceptionComponent = Controller->FindComponentByClass<UKAIPerceptionComponent>();
      if(PerceptionComponent) {
        Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetVisibleCharacter());
      }
    }
  }
  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}