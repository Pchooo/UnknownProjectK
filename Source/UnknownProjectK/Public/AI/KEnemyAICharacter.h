

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KEnemyAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class UNKNOWNPROJECTK_API AKEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AKEnemyAICharacter();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category= "AI")
	UBehaviorTree* BehaviorTreeAsset; 
	
};
