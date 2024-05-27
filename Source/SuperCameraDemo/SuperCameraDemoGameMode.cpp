// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperCameraDemoGameMode.h"
#include "SuperCameraDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SuperCameraDemoPlayerController.h"

ASuperCameraDemoGameMode::ASuperCameraDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ASuperCameraDemoPlayerController::StaticClass();
}
