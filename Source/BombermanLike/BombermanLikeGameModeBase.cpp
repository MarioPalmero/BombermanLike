// - Mario Palmero [2017], zlib/libpng licensed.

#include "BombermanLikeGameModeBase.h"
#include "Engine.h"
#include "ConstructorHelpers.h"
#include "Pawns/Public/BombermanPawn.h"

ABombermanLikeGameModeBase::ABombermanLikeGameModeBase() : Super(),
	NumPlayers(1),
	m_lastMatchResult(EMatchResult::ResultDraw),
	m_scorePlayer1(0),
	m_scorePlayer2(0)
{
	// Initial Classes Set up
	PlayerControllerClass = AUIPlayerController::StaticClass(); 

	static ConstructorHelpers::FClassFinder<ABombermanPawn> pawnLoader(TEXT("Blueprint'/Game/Gameplay/Core/BP_BombermanPawn.BP_BombermanPawn_C'"));
	if (pawnLoader.Class != nullptr)
		DefaultPawnClass = pawnLoader.Class;

	// Following RAII we initialize and destroy resources properly
	m_gameState = new GameModeFSM();

	PrimaryActorTick.bCanEverTick = true;
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

void ABombermanLikeGameModeBase::NotifyEndEndMatch()
{
	m_gameState->SetState(EGameModeStates::Match);
}

void ABombermanLikeGameModeBase::NotifyPlayerStatusAfterMatch(bool bIsPlayer1Alive, bool bIsPlayer2Alive)
{
	if (bIsPlayer1Alive == bIsPlayer2Alive)
	{
		m_lastMatchResult = EMatchResult::ResultDraw;
	}
	else if (bIsPlayer1Alive)
	{
		m_lastMatchResult = EMatchResult::ResultPlayer1;
		++m_scorePlayer1;
	}
	else
	{
		m_lastMatchResult = EMatchResult::ResultPlayer2;
		++m_scorePlayer2;
	}
}

EMatchResult ABombermanLikeGameModeBase::GetLastMatchResult() const
{
	return m_lastMatchResult;
}

int ABombermanLikeGameModeBase::GetScore(int player) const
{
	if (player == 0)
		return m_scorePlayer1;
	else if(player == 1)
		return m_scorePlayer2;
	return 0;
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
				ClearInputFromController(oldPlayerController);
				oldPlayerController->SetActorTickEnabled(false);
				newPlayerController->SetPlayer(player);

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

void ABombermanLikeGameModeBase::ClearInputFromController(APlayerController* controller)
{
	controller->PlayerInput->FlushPressedKeys();
	controller->InputComponent->ClearBindingValues();
	controller->DisableInput(controller);
	controller->EnableInput(controller);
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
