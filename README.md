# SuperCameraDemo


## 1、Replace USpringArmComponent and UCameraComponent

In your Character, use USuperSpringArmComponent and USuperCameraComponent to replace USpringArmComponent and UCameraComponent.


## 2、 Init ASuperPlayerCameraManager

You can init ASuperPlayerCameraManager In your PlayerController.

```
void ADemoPlayerController::ClientRestart_Implementation(APawn* NewPawn)
{
	Super::ClientRestart_Implementation(NewPawn);

	if (ASuperPlayerCameraManager* CameraManager = Cast<ASuperPlayerCameraManager>(PlayerCameraManager))
	{
		if (AMSPlayerCharacter* PlayerCharacter = Cast<AMSPlayerCharacter>(GetCharacter()))
		{
			USuperSpringArmComponent* SpringArm = PlayerCharacter->GetSpringArm();
			USuperCameraComponent* Camera = PlayerCharacter->GetCamera();
			CameraManager->Init(SpringArm, Camera);
		}
	}
}
```


## 3、Set PlayerCameraManager class in your PlayerController

You can set PlayerCameraManager class with ASuperPlayerCameraManager in your BP_PlayerController class


## 4、AddCameraMotion and RemoveCameraMotion

You can add/remove a CameraMotion use function AddCameraMotion/RemoveCameraMotion


## 5、Debug

You can debug the CameraMotion info by GameplayDebuggerCategory;