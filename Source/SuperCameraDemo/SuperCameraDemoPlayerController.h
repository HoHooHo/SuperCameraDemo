// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SuperCameraDemoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SUPERCAMERADEMO_API ASuperCameraDemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASuperCameraDemoPlayerController();
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
	
};
