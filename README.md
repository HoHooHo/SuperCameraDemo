# SuperCameraDemo


## 1、Add "SuperCamera" to PublicDependencyModuleNames in your Build.cs

```
// SuperCameraDemo.Build.cs
public class SuperCameraDemo : ModuleRules
{
	public SuperCameraDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "SuperCamera" });
	}
}
```

## 2、Replace USpringArmComponent and UCameraComponent

In your Character, use USuperSpringArmComponent and USuperCameraComponent to replace USpringArmComponent and UCameraComponent.

```
	// ASuperCameraDemoCharacter.h
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USuperSpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USuperCameraComponent* FollowCamera;
```

```
	// ASuperCameraDemoCharacter.cpp
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USuperSpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<USuperCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USuperSpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
```

## 3、 Init ASuperPlayerCameraManager

You can init ASuperPlayerCameraManager In your PlayerController.

```
// ASuperCameraDemoPlayerController.cpp
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
```


## 4、Set PlayerCameraManager class in your PlayerController

### 4.1 Set ASuperCameraDemoPlayerController to PlayerControllerClass in GameMode

```
// ASuperCameraDemoGameMode.cpp
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
```

### 4.2 Set ASuperPlayerCameraManager to PlayerCameraManagerClass in PlayerController
```
// ASuperCameraDemoPlayerController.cpp
ASuperCameraDemoPlayerController::ASuperCameraDemoPlayerController()
{
	PlayerCameraManagerClass = ASuperPlayerCameraManager::StaticClass();
}
```

## 5、AddCameraMotion and RemoveCameraMotion

You can add/remove a CameraMotion use function AddCameraMotion/RemoveCameraMotion

![image](https://github.com/HoHooHo/SuperCameraDemo/blob/main/img/TestCameraMotion.png)


## 6、Debug info

You can debug the CameraMotion info by GameplayDebuggerCategory;
