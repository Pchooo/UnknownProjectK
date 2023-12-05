#include "AI/KEnemyAICharacter.h"
#include "AI/KEnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AKEnemyAICharacter::AKEnemyAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKEnemyAIController::StaticClass();

    if(GetCharacterMovement()) {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0,200,0);
    }
    bUseControllerRotationYaw = false; 
}



