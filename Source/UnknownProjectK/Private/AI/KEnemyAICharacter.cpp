#include "AI/KEnemyAICharacter.h"
#include "AI/KEnemyAIController.h"


AKEnemyAICharacter::AKEnemyAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKEnemyAIController::StaticClass();
}



