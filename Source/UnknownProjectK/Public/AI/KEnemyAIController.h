// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWNPROJECTK_API AKEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn *InPawn) override;
	
};
