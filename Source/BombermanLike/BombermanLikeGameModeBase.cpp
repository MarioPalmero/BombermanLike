// - Mario Palmero [2017], zlib/libpng licensed.

#include "BombermanLikeGameModeBase.h"
#include "Engine.h"
#include "ConstructorHelpers.h"
#include "Pawns/Public/BombermanPawn.h"

ABombermanLikeGameModeBase::ABombermanLikeGameModeBase() : Super()
{
	// Initial Classes Set up
	PlayerControllerClass = AUIPlayerController::StaticClass(); 

	static ConstructorHelpers::FClassFinder<ABombermanPawn> pawnLoader(TEXT("Blueprint'/Game/Gameplay/Core/BP_BombermanPawn.BP_BombermanPawn_C'"));
	if (pawnLoader.Class != nullptr)
		DefaultPawnClass = pawnLoader.Class;

	// Following RAII we initialize and destroy resources properly
	m_gameState = new GameModeFSM();

	SetActorTickEnabled(true);
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

void ABombermanLikeGameModeBase::NotifyEndSplash()
{
	m_gameState->SetState(EGameModeStates::CharacterSelection);
}

void ABombermanLikeGameModeBase::NotifyEndCharacterSelection()
{
	m_gameState->SetState(EGameModeStates::Match);
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

				AActor* oldViewTarget = oldPlayerController->GetViewTarget();

				// Possess the pawn with the new controller and acknowledge it
				newPlayerController->Possess(pawn);
				newPlayerController->AcknowledgePossession(pawn);
				newPlayerController->SetActorTickEnabled(true);
				newPlayerController->SetViewTarget(oldViewTarget);

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
