#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include <Windows.h>
#include <string>
#include <vector>

class StateMachineExampleGame;

class GamePlayState :
    public GameState
{
    StateMachineExampleGame* m_pOwner;

    Player m_player;
    Level* m_plevel;

    bool m_beatLevel;
    int m_skipFrameCount;
    static constexpr int kFramesToSkip = 2;

    int m_currentLevel;
    std::vector<std::string> m_LevelNames;

public:
    GamePlayState(StateMachineExampleGame* pOwner);
    ~GamePlayState();
    virtual void Enter() override;
    virtual bool Update(bool processInput = true) override;
    virtual void Draw() override;

private:
    bool Load();
    void HandleCollision(int newPlayerX, int newPlayerY);
    void DrawHUD(const HANDLE& console);
};

