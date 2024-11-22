// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSMobileGameMode.h"
#include "FPSMobileCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSMobileGameMode::AFPSMobileGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
