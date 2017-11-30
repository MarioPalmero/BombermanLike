// - Mario Palmero [2017], zlib/libpng licensed.

#include "GameFlow/Public/GameModeFSM.h"
#include "EngineUtils.h"
#include "BombermanLikeGameModeBase.h"
#include "Map/Public/MapManager.h"
#include "Kismet/GameplayStatics.h"


GameModeFSM::GameModeFSM() : FSM(EGameModeStates::Splash),
	m_gameMode(nullptr)
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
		m_UIControllers[0]->EndSplashScreen();
}

void GameModeFSM::BeginCharacterSelection(EGameModeStates previousState)
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
		m_UIControllers[0]->StartCharacterSelectionScreen();
}

void GameModeFSM::UpdateCharacterSelection(float DeltaTime)
{

}

void GameModeFSM::EndCharacterSelection(EGameModeStates nextState)
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

	// Check if the number of players don't match with the number of registered controllers
	while (m_UIControllers.Num() < m_gameMode->GetNumPlayers())
	{
		AUIPlayerController* controller = Cast<AUIPlayerController>(UGameplayStatics::GetPlayerController(m_gameMode->GetWorld(), m_UIControllers.Num()));
		m_UIControllers.Add(controller);
	}

	if (m_UIControllers.Num() >= 1 && m_UIControllers[0] != nullptr)
		m_UIControllers[0]->EndCharacterSelectionScreen();
}

void GameModeFSM::BeginMatch(EGameModeStates previousState)
{
	if (previousState != EGameModeStates::Match)
	{
		if (m_gameMode != nullptr)
		{
			// Should only be executed the first match
			while (m_matchControllers.Num() < m_UIControllers.Num())
			{
				m_matchControllers.Add(m_gameMode->GetWorld()->SpawnActor<AMatchPlayerController>(AMatchPlayerController::StaticClass()));
			}

			// Swaping UI controllers by Match controllers
			for (int controllerIndex = 0; controllerIndex < m_matchControllers.Num() && controllerIndex < m_UIControllers.Num(); ++controllerIndex)
			{
				ABombermanLikeGameModeBase::SwapPlayerController(m_UIControllers[controllerIndex]->GetPawn(), m_matchControllers[controllerIndex]);
			}

			AMapManager::GetInstance()->PlaceDestructibleBlocks();
		}
	}
}

void GameModeFSM::UpdateMatch(float DeltaTime)
{

}

void GameModeFSM::EndMatch(EGameModeStates nextState)
{

}

void GameModeFSM::BeginEndMatch(EGameModeStates previousState)
{

}

void GameModeFSM::UpdateEndMatch(float DeltaTime)
{

}

void GameModeFSM::EndEndMatch(EGameModeStates nextState)
{

}
