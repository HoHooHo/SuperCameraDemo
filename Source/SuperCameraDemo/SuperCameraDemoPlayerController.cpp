// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperCameraDemoPlayerController.h"
#include "SuperCameraDemoCharacter.h"
#include "SuperPlayerCameraManager.h"
#include "SuperSpringArmComponent.h"
#include "SuperCameraComponent.h"

ASuperCameraDemoPlayerController::ASuperCameraDemoPlayerController()
{
	PlayerCameraManagerClass = ASuperPlayerCameraManager::StaticClass();
}

void ASuperCameraDemoPlayerController::ClientRestart_Implementation(APawn* NewPawn)
{
	Super::ClientRestart_Implementation(NewPawn);

	if (ASuperPlayerCameraManager* CameraManager = Cast<ASuperPlayerCameraManager>(PlayerCameraManager))
	{
		if (ASuperCameraDemoCharacter* PlayerCharacter = Cast<ASuperCameraDemoCharacter>(GetCharacter()))
		{
			USuperSpringArmComponent* SpringArm = PlayerCharacter->GetCameraBoom();
			USuperCameraComponent* Camera = PlayerCharacter->GetFollowCamera();
			CameraManager->Init(SpringArm, Camera);
		}
	}
}