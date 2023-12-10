// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "../UnknownProjectKCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogPer, All, All)

AActor *UKAIPerceptionComponent::GetVisibleCharacter()
{
  TArray<AActor*> PercievedActors;
  GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);

  if(PercievedActors.IsEmpty()) {
    return nullptr;
  }

  for(const auto PercievedActor : PercievedActors)
  {
    if(Cast<AUnknownProjectKCharacter>(PercievedActor)) {
      return PercievedActor;
    }
  }
  return nullptr;
}