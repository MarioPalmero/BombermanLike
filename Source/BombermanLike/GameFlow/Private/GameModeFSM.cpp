// - Mario Palmero [2017], zlib/libpng licensed.

#include "GameFlow/Public/GameModeFSM.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "BombermanLikeGameModeBase.h"
#include "Pawns/Public/BombermanPawn.h"
#include "Map/Public/MapManager.h"
#include "Kismet/GameplayStatics.h"


GameModeFSM::GameModeFSM() : FSM(EGameModeStates::Splash),
	m_gameMode(nullptr),
	m_matchTimer(0.0f)
{
	InitializeFunctions();
}

GameModeFSM::GameModeFSM(EGameModeStates initialState) : FSM(initialState),
	m_gameMode(nullptr)
{
	InitializeFunctions();
}

void GameModeFSM::Initialize(ABombermanLikeGameModeBase * gameMode)
{
	m_gameMode = gameMode;
}

void GameModeFSM::InitializeFunctions()
{
	// Splash functions
	SetBeginStateFunction(EGameModeStates::Splash, [&](EGameModeStates e) {BeginSplash(e);});
	SetEndStateFunction(EGameModeStates::Splash, [&](EGameModeStates e) {EndSplash(e);});
	SetUpdateFunction(EGameModeStates::Splash, [&](float t) {UpdateSplash(t);});

	// Character Selection functions
	SetBeginStateFunction(EGameModeStates::CharacterSelection, [&](EGameModeStates e) {BeginCharacterSelection(e);});
	SetEndStateFunction(EGameModeStates::CharacterSelection, [&](EGameModeStates e) {EndCharacterSelection(e);});
	SetUpdateFunction(EGameModeStates::CharacterSelection, [&](float t) {UpdateCharacterSelection(t);});

	// Match functions
	SetBeginStateFunction(EGameModeStates::Match, [&](EGameModeStates e) {BeginMatch(e);});
	SetEndStateFunction(EGameModeStates::Match, [&](EGameModeStates e) {EndMatch(e);});
	SetUpdateFunction(EGameModeStates::Match, [&](float t) {UpdateMatch(t);});

	// End Game functions
	SetBeginStateFunction(EGameModeStates::EndMatch, [&](EGameModeStates e) {BeginEndMatch(e);});
	SetEndStateFunction(EGameModeStates::EndMatch, [&](EGameModeStates e) {EndEndMatch(e);});
	SetUpdateFunction(EGameModeStates::EndMatch, [&](float t) {UpdateEndMatch(t);});
}

void GameModeFSM::BeginSplash(EGameModeStates previousState)
{
	if (m_UIControllers.Num() <= 0)
	{
		if (m_gameMode != nullptr)
		{
			AUIPlayerController* controller = Cast<AUIPlayerController>(m_gameMode->GetWorld()->GetFirstPlayerController());
			if (controller != nullptr)
				m_UIControllers.Add(controller);
		}
	}

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->StartSplashScreen();
}

void GameModeFSM::UpdateSplash(float DeltaTime)
{
}

void GameModeFSM::EndSplash(EGameModeStates nextState)
{
	for (AUIPlayerController* controller : m_UIControllers)
		ABombermanLikeGameModeBase::ClearInputFromController(controller);

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->EndSplashScreen();
}

void GameModeFSM::BeginCharacterSelection(EGameModeStates previousState)
{
	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->StartCharacterSelectionScreen();
}

void GameModeFSM::UpdateCharacterSelection(float DeltaTime)
{

}

void GameModeFSM::EndCharacterSelection(EGameModeStates nextState)
{
	// Check if the number of players don't match with the number of registered controllers
	while (m_UIControllers.Num() < m_gameMode->NumPlayers)
	{
		AUIPlayerController* controller = Cast<AUIPlayerController>(UGameplayStatics::GetPlayerController(m_gameMode->GetWorld(), m_UIControllers.Num()));
		m_UIControllers.Add(controller);
	}

	for (AUIPlayerController* controller : m_UIControllers)
		ABombermanLikeGameModeBase::ClearInputFromController(controller);

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->EndCharacterSelectionScreen();
}

void GameModeFSM::BeginMatch(EGameModeStates previousState)
{
	if (previousState != EGameModeStates::Match)
	{
		if (m_gameMode != nullptr)
		{
			m_matchTimer = m_gameMode->MatchDuration;

			// Should only be executed the first match
			while (m_matchControllers.Num() < m_UIControllers.Num())
			{
				m_matchControllers.Add(m_gameMode->GetWorld()->SpawnActor<AMatchPlayerController>(AMatchPlayerController::StaticClass()));
			}

			TArray<APlayerStart*> startPoints;
			for (TActorIterator<APlayerStart> startPointItr(m_gameMode->GetWorld()); startPointItr; ++startPointItr)
				startPoints.Add(*startPointItr);

			// Resetting pawns and Swaping UI controllers by Match controllers
			for (int controllerIndex = 0; controllerIndex < m_matchControllers.Num() && controllerIndex < m_UIControllers.Num() && controllerIndex < startPoints.Num(); ++controllerIndex)
			{
				ABombermanPawn* pawn = Cast<ABombermanPawn>(m_UIControllers[controllerIndex]->GetPawn());
				pawn->Resurrect();

				ABombermanLikeGameModeBase::SwapPlayerController(m_UIControllers[controllerIndex]->GetPawn(), m_matchControllers[controllerIndex]);
				// Set position and colour
				pawn->SetActorLocation(startPoints[controllerIndex]->GetActorLocation());
				pawn->AssignColour(m_matchControllers[controllerIndex]->GetLocalPlayer()->GetControllerId() == 0 ? FColor::Blue : FColor::Green);
			}

			AMapManager::GetInstance()->PlaceDestructibleBlocks();
		}
	}
}

void GameModeFSM::UpdateMatch(float DeltaTime)
{
	// We do this check to call just once the ShowCountdown function
	bool bShouldShowCountdown = m_matchTimer > 10.0f && m_matchTimer - DeltaTime <= 10.0f;
	m_matchTimer -= DeltaTime;

	bool bSomebodyDead = false;
	// We look for dead players and also check if the countdown should be shown
	for (AMatchPlayerController* controller : m_matchControllers)
	{
		ABombermanPawn* pawn = Cast<ABombermanPawn>(controller->GetPawn());
		if(pawn != nullptr)
			bSomebodyDead = bSomebodyDead || pawn->bIsDead;

		if (bShouldShowCountdown && controller->GetLocalPlayer()->GetControllerId() == 0)
			controller->ShowCountdown(FMath::FloorToInt(m_matchTimer) + 1);
	}

	// If somebody is dead or the timer has expired the match has to end
	if(bSomebodyDead || m_matchTimer < 0.0f)
	{
		bool bIsPlayer1Alive = false, bIsPlayer2Alive = false;

		// The match has ended so we notify the score to the game mode
		for (AMatchPlayerController* controller : m_matchControllers)
		{
			ABombermanPawn* pawn = Cast<ABombermanPawn>(controller->GetPawn());
			if (controller->GetLocalPlayer()->GetControllerId() == 0 && pawn != nullptr)
				bIsPlayer1Alive = !pawn->bIsDead;
			else if (controller->GetLocalPlayer()->GetControllerId() == 1 && pawn != nullptr)
				bIsPlayer2Alive = !pawn->bIsDead;
		}

		m_gameMode->NotifyPlayerStatusAfterMatch(bIsPlayer1Alive, bIsPlayer2Alive);
		SetState(EGameModeStates::EndMatch);
	}
}

void GameModeFSM::EndMatch(EGameModeStates nextState)
{

}

void GameModeFSM::BeginEndMatch(EGameModeStates previousState)
{
	// Swaping UI controllers by Match controllers
	for (int controllerIndex = 0; controllerIndex < m_matchControllers.Num() && controllerIndex < m_UIControllers.Num(); ++controllerIndex)
	{
		ABombermanLikeGameModeBase::SwapPlayerController(m_matchControllers[controllerIndex]->GetPawn(), m_UIControllers[controllerIndex]);
	}

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->StartEndMatchScreen();
}

void GameModeFSM::UpdateEndMatch(float DeltaTime)
{

}

void GameModeFSM::EndEndMatch(EGameModeStates nextState)
{
	for (AUIPlayerController* controller : m_UIControllers)
		ABombermanLikeGameModeBase::ClearInputFromController(controller);

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->EndEndMatchScreen();
}
