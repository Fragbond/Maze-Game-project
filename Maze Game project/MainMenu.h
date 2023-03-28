#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenu :
    public GameState
{
    StateMachineExampleGame* m_pOwner;
public:
    MainMenu(StateMachineExampleGame* pOwner);
    ~MainMenu() = default;

    virtual bool Update(bool processInput = true) override;
    virtual void Draw() override;
};

