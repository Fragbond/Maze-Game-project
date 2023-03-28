#include "StateMachineExampleGame.h"
#include "Game.h"
#include "MainMenu.h"
#include "GamePlayState.h"
#include "SettingState.h"
#include "HighScoreState.h"
#include "WinState.h"
#include "LoseState.h"

StateMachineExampleGame::StateMachineExampleGame(Game* pOwner)
	:m_pOwner(pOwner)
	, m_pCurrentState(nullptr)
	, m_pNewState(nullptr)
{

}

bool StateMachineExampleGame::Init()
{
	LoadScene(SceneName::MainMenu);
	return true;
}
bool StateMachineExampleGame::UpdateCurrentState(bool processInput)
{
	bool done = false;
	if (m_pNewState != nullptr)
	{
		ChangeState(m_pNewState);
		m_pNewState = nullptr;
	}

	if (m_pCurrentState != nullptr)
	{
		done = m_pCurrentState->Update(processInput);
	}
	return done;
}
void StateMachineExampleGame::DrawCurrentState()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Draw();
	}
}
void StateMachineExampleGame::ChangeState(GameState* pNewState)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->ExitGameState();
	}

	delete m_pCurrentState;
	m_pCurrentState = pNewState;
	pNewState->Enter();
}
void StateMachineExampleGame::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case SceneName::MainMenu:
		m_pNewState = new MainMenu(this);
		break;
	case SceneName::GamePlay:
		m_pNewState = new GamePlayState(this);
		break;
	case SceneName::Settings:
		m_pNewState = new SettingState(this);
		break;
	case SceneName::Highscore:
		m_pNewState = new HighScoreState(this);
		break;
	case SceneName::Win:
		m_pNewState = new WinState(this);
		break;
	case SceneName::Lose:
		m_pNewState = new LoseState(this);
		break;
	default:
		break;
	}
}
void StateMachineExampleGame::CleanUp()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->ExitGameState();
		delete m_pCurrentState;
	}
}