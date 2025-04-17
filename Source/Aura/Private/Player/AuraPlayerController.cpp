// CopyrightVIkasAuraProject


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (Cast<IEnemyInterface>(LastActor.GetInterface()) == nullptr)
	{
		if (Cast<IEnemyInterface>(ThisActor.GetInterface()) != nullptr)
		{
			//case B
			ThisActor->HighlightActor();
			/*if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("ThisActor->HighlightActor()"));*/	
		}
		else
		{
			//case A - both are null and do nothing
			/*if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Case A"));*/
			
		}
	}
	else // LastActor is valid
	{
		if (Cast<IEnemyInterface>(ThisActor.GetInterface()) == nullptr)
		{
			//case C
			LastActor->UnHighlightActor();
			/*if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("LastActor->UnHighlightActor()"));*/
		}
		else //both actors are valid
		{
			if (LastActor != ThisActor)
			{
				//case B
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();

				/*if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("LastActor->UnHighlightActor()... ThisActor->HighlightActor()"));*/
				
			}
			else
			{
				// case E - do nothing
				/*if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Case E"));*/
			}
		}
	}
	
	
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(SubSystem);
	SubSystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor= true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


