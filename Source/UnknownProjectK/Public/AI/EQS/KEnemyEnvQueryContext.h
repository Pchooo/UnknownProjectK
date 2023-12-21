// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "KEnemyEnvQueryContext.generated.h"

/**
 *
 */
UCLASS()
class UNKNOWNPROJECTK_API UKEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	void ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor"; 
};
