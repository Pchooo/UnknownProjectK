// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "KAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWNPROJECTK_API UKAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
  AActor* GetVisibleCharacter();
};
