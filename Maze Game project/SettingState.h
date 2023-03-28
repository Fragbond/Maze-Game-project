#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingState :
    public GameState
{
    StateMachineExampleGame* m_pOwner;

public:
    SettingState(StateMachineExampleGame* pOwner);
    ~SettingState() = default;

    virtual bool Update(bool processInput = true) override;
    virtual void Draw() override;
};

