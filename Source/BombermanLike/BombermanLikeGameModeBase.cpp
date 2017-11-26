// - Mario Palmero [2017], zlib/libpng licensed.

#include "BombermanLikeGameModeBase.h"
#include "Pawns/Public/BombermanPawn.h"

ABombermanLikeGameModeBase::ABombermanLikeGameModeBase() : Super()
{
	// Initial Classes Set up
	PlayerControllerClass = AUIPlayerController::StaticClass();
	DefaultPawnClass = ABombermanPawn::StaticClass();

	// Following RAII we initialize and destroy resources properly
	m_gameState = new GameModeFSM();
}

ABombermanLikeGameModeBase::~ABombermanLikeGameModeBase()
{
	// Following RAII we initialize and destroy resources properly
	delete m_gameState;
}

EGameModeStates ABombermanLikeGameModeBase::GetCurrentState() const
{
	return m_gameState->GetCurrentState();
}

void ABombermanLikeGameModeBase::SwapPlayerController(APawn * pawn, APlayerController * newPlayerController)
{
	if (pawn != nullptr && pawn->GetController() != nullptr)
	{
		// Get the controller from the pawn
		APlayerController* oldPlayerController = Cast<APlayerController>(pawn->GetController());
		if (oldPlayerController != nullptr)
		{
			UPlayer* player = oldPlayerController->Player;
			if (player != nullptr)
			{
				newPlayerController->SetPlayer(player);
				oldPlayerController->SetActorTickEnabled(false);

				// Possess the pawn with the new controller and acknowledge it
				newPlayerController->Possess(pawn);
				newPlayerController->AcknowledgePossession(pawn);
				newPlayerController->SetActorTickEnabled(true);

				// Clean old input component
				if (oldPlayerController->InputComponent)
					oldPlayerController->DisableInput(oldPlayerController);

				// Prepare new input component
				if(newPlayerController->InputComponent)
					newPlayerController->EnableInput(newPlayerController);
			}
		}
	}
}


void ABombermanLikeGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	m_gameState->Update(DeltaSeconds);
}

void ABombermanLikeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	m_gameState->Initialize(this);
	m_gameState->SetState(EGameModeStates::Splash);
}
