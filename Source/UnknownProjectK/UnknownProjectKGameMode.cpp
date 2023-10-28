// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnknownProjectKGameMode.h"
#include "UnknownProjectKCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnknownProjectKGameMode::AUnknownProjectKGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
