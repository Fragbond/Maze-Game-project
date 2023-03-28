#include "GamePlayState.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Exit.h"
#include <assert.h>
#include "AudioManager.h"
#include "Lava.h"
#include "StateMachineExampleGame.h"
#include "Utility.h"
#include "Teleporter.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GamePlayState::GamePlayState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
	,m_beatLevel(false)
    ,m_skipFrameCount(0)
    ,m_currentLevel(0)
    ,m_plevel(nullptr)
{ 
    //m_LevelNames.push_back("TeleporterTest.txt");
    m_LevelNames.push_back("level1.txt");
    //m_LevelNames.push_back("level2.txt");
    m_LevelNames.push_back("level3.txt");
}

GamePlayState::~GamePlayState()
{
    delete m_plevel;
    m_plevel = nullptr;
}

bool GamePlayState::Load()
{
    if (m_plevel)
    {
        delete m_plevel;
        m_plevel = nullptr;
    }

    m_plevel = new Level();

	return m_plevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void GamePlayState::Enter()
{
	Load();
}

bool GamePlayState::Update(bool processInput)
{
    if (processInput && !m_beatLevel)
    {
        int input = _getch();
        int arrowInput = 0;
        int newPlayerX = m_player.GetXPosition();
        int newPlayerY = m_player.GetYPosition();

        if (input == kArrowInput)
        {
            arrowInput = _getch();
        }

        if ((input == kArrowInput && arrowInput == kLeftArrow) ||
            (char)input == 'A' || (char)input == 'a')
        {
            newPlayerX--;
        }

        if ((input == kArrowInput && arrowInput == kLeftArrow) ||
            (char)input == 'D' || (char)input == 'd')
        {
            newPlayerX++;
        }
        else if ((input == kArrowInput && arrowInput == kRightArrow) ||
            (char)input == 'W' || (char)input == 'w')
        {
            newPlayerY--;
        }
        else if ((input == kArrowInput && arrowInput == kRightArrow) ||
            (char)input == 'S' || (char)input == 's')
        {
            newPlayerY++;
        }
        else if (input == kEscapeKey)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
        }
        else if ((char)input == 'Z' || (char)input == 'z')
        {
            m_player.DropKey();
        }

        if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
        {
            return false;
        }
        else
        {
            HandleCollision(newPlayerX, newPlayerY);
        }

    }
    if (m_beatLevel)
    {
        ++m_skipFrameCount;
        if (m_skipFrameCount > kFramesToSkip)
        {
            m_beatLevel = false;
            m_skipFrameCount = 0;

            ++m_currentLevel;
            if (m_currentLevel == m_LevelNames.size())
            {
                Utility::WriteHighScore(m_player.GetMoney());
                AudioManager::GetInstance()->PlayWinSound();
                m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
            }
            else
            {
                Load();
            }

        }
    }
    return false;
}

void GamePlayState::HandleCollision(int newPlayerX, int newPlayerY)
{
    bool isGameDone = false;
    PlacableActor* collidedActor = m_plevel->UpdateActors(newPlayerX, newPlayerY);
    if (collidedActor != nullptr && collidedActor->IsActive())
    {
        switch (collidedActor->GetType())
        {
        case ActorType::Teleporter:
        {
            Teleporter* collidedTeleporter = dynamic_cast<Teleporter*>(collidedActor);
            assert(collidedTeleporter);
            m_player.SetPosition(collidedTeleporter->GetOtherTeleporter()->GetXPosition(), collidedTeleporter->GetOtherTeleporter()->GetYPosition());

            break;
        }
        case ActorType::Lava:
        {
            Lava* collidedLava = dynamic_cast<Lava*>(collidedActor);
            assert(collidedLava);
            m_player.SetPosition(newPlayerX, newPlayerY);
            if (collidedLava)
            {
                AudioManager::GetInstance()->PlayLoseSound();
                m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
            }
            break;
        }
        case ActorType::Enemy:
        {
            Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
            assert(collidedEnemy);
            AudioManager::GetInstance()->PlayLoseLivesSound();
            collidedEnemy->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);

            m_player.DecrementLives();
            if (m_player.GetLives() < 0)
            {
                AudioManager::GetInstance()->PlayLoseSound();
                m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
            }
            break;
        }
        case ActorType::Money:
        {
            Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
            assert(collidedMoney);
            AudioManager::GetInstance()->PlayMoneySound();
            collidedMoney->Remove();
            m_player.AddMoney(collidedMoney->GetWorth());
            m_player.SetPosition(newPlayerX, newPlayerY);
            break;
        }
        case ActorType::Key:
        {
            Key* collidedKey = dynamic_cast<Key*>(collidedActor);
            assert(collidedKey);
            if (!m_player.HasKey())
            {
                m_player.PickUpKey(collidedKey);
                collidedKey->Remove();
                m_player.SetPosition(newPlayerX, newPlayerY);
                AudioManager::GetInstance()->PlayPickUpKeySound();
            }
            break;
        }
        case ActorType::Door:
        {
            Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
            assert(collidedDoor);
            if (!collidedDoor->IsOpen())
            {
                if (m_player.HasKey(collidedDoor->GetColor()))
                {
                    collidedDoor->Open();
                    collidedDoor->Remove();
                    m_player.UseKey();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    AudioManager::GetInstance()->PlayDoorOpenSound();
                }
                else
                {
                    AudioManager::GetInstance()->PlayDoorClosedSound();
                }


            }
            else
            {
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
            break;
        }
        case ActorType::Exit:
        {
            Exit* collidedExit = dynamic_cast<Exit*>(collidedActor);
            assert(collidedExit);
            collidedExit->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);
            m_beatLevel = true;
            break;
        }
        default:
            break;

        }


    }
    else if (m_plevel->IsSpace(newPlayerX, newPlayerY)) // no collision
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_plevel->IsWall(newPlayerX, newPlayerY))
    {
        // wall collision, do nothing
    }

}

void GamePlayState::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    m_plevel->Draw();

    //Set cursor position for player
    COORD actorCursorPosition;
    actorCursorPosition.X = m_player.GetXPosition();
    actorCursorPosition.Y = m_player.GetYPosition();
    SetConsoleCursorPosition(console, actorCursorPosition);
    m_player.Draw();

    // Set the cursor to the end of the level
    COORD currentCursorPosition;
    currentCursorPosition.X = 0;
    currentCursorPosition.Y = m_plevel->GetHeight();
    SetConsoleCursorPosition(console, currentCursorPosition);

    DrawHUD(console);
}

void GamePlayState::DrawHUD(const HANDLE& console)
{
    cout << endl;

    // Top Border
    for (int i = 0; i < m_plevel->GetWidth(); ++i)
    {
        cout << Level::WAL;
    }
    cout << endl;

    // Left Border
    cout << Level::WAL;

    cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;
    cout << " $: " << m_player.GetMoney() << " " << Level::WAL;
    cout << " lives: " << m_player.GetLives() << " " << Level::WAL;
    cout << " key: ";
    if (m_player.HasKey())
    {
        m_player.GetKey()->Draw();
    }
    else
    {
        cout << " ";
    }

    // Right border
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);

    COORD pos;
    pos.X = m_plevel->GetHeight() - 1;
    pos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(console, pos);

    cout << Level::WAL;
    cout << endl;

    // Bottom border
    for (int i = 0; i < m_plevel->GetWidth(); ++i)
    {
        cout << Level::WAL;
    }
    cout << endl;
}