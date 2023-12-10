// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KEnemyAIController.generated.h"

class UKAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class UNKNOWNPROJECTK_API AKEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AKEnemyAIController();
protected:
	virtual void OnPossess(APawn *InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UKAIPerceptionComponent* KPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FName FocusOnKey = "EnemyActor";

	virtual void Tick(float DeltaSeconds) override;
private:
	AActor* GetFocusOnActor();
};
