#include "Game.h"

Game::Game()
    : m_pStateMachine(nullptr)

{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
    if (pStateMachine)
    {
        pStateMachine->Init();
        m_pStateMachine = pStateMachine;
    }
}
void Game::RunGameLoop()
{
    bool isGameOver = false;
    while (!isGameOver)
    {
        update(false);
        draw();
        isGameOver = update(true);
    }
    draw();
}
void Game::Deinitialize()
{
    if (m_pStateMachine)
    {
        m_pStateMachine->CleanUp();
    }
}
bool Game::update(bool processInput)
{
    return m_pStateMachine->UpdateCurrentState(processInput);
}
void Game::draw()
{
    m_pStateMachine->DrawCurrentState();
}


