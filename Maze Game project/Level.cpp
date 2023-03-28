#include <iostream>
#include <fstream>
#include <windows.h>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Exit.h"
#include "Money.h"
#include <assert.h>
#include "Lava.h"
#include "Teleporter.h"

using namespace std;


Level::Level()
	:m_plevelData(nullptr)
	,m_height(0)
	,m_width(0)
{

}
Level::~Level()
{
	if (m_plevelData != nullptr)
	{
		delete[] m_plevelData;
		m_plevelData = nullptr;
	}

    while (!m_pActors.empty())
    {
        delete m_pActors.back();
        m_pActors.pop_back();
    }
}

bool Level::Load(std::string levelName, int* PlayerX, int* PlayerY)
{
    levelName.insert(0, "../");

    ifstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening file failed." << endl;
        return false;
    }
    else
    {
        constexpr int tempSize = 25;
        char temp[tempSize];

        levelFile.getline(temp, tempSize, '\n');
        m_width = atoi(temp);

        levelFile.getline(temp, tempSize, '\n');
        m_height = atoi(temp);

        m_plevelData = new char[m_width * m_height];
        levelFile.read(m_plevelData, (long long)m_width * (long long)m_height);
        
        bool anyWarnings = Convert(PlayerX, PlayerY);
        if (anyWarnings)
        {
            cout << "There was an error in loading the level." << endl;
            system("pause");
        }
        return true;
        
    }
}
void Level::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (int)ActorColor::Regular);

    for (int y = 0; y < GetHeight(); ++y)
    {
        for (int x = 0; x < GetWidth(); ++x)
        {
            int indexToPrint = GetIndexFromCoordinates(x, y);
            cout << m_plevelData[indexToPrint];
        }
        cout << endl;
    }
    COORD actorCursorPosition;

    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
    {
        if ((*actor)->IsActive())
        {
            actorCursorPosition.X = (*actor)->GetXPosition();
            actorCursorPosition.Y = (*actor)->GetYPosition();
            SetConsoleCursorPosition(console, actorCursorPosition);
            (*actor)->Draw();
        }
    }
}



bool Level::IsSpace(int x, int y)
{
    return m_plevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsWall(int x, int y)
{
    return m_plevelData[GetIndexFromCoordinates(x, y)] == WAL;
}

bool Level::Convert(int* PlayerX, int* PlayerY)
{
    Teleporter* pFirstBlueTeleporter = nullptr;
    Teleporter* pFirstRedTeleporter = nullptr;
    Teleporter* pFirstGreenTeleporter = nullptr;
    bool anyWarnings = false;
    for (int y = 0; y < m_height; y++)
    {


        for (int x = 0; x < m_width; x++)
        {
            int index = GetIndexFromCoordinates(x, y);

            switch (m_plevelData[index])
            {
            case '+':
            case '-':
            case '|':
                m_plevelData[index] = WAL;
                break;
            case 'O':
                if (pFirstBlueTeleporter == nullptr)
                {
                    pFirstBlueTeleporter = new Teleporter(x, y, ActorColor::Blue);
                    m_pActors.push_back(pFirstBlueTeleporter);
                }
                else
                {
                    Teleporter* pSecondBlueTeleporter = new Teleporter(x, y, ActorColor::Blue);
                    m_pActors.push_back(pSecondBlueTeleporter);
                    pFirstBlueTeleporter->SetOtherTeleporter(pSecondBlueTeleporter);
                    pSecondBlueTeleporter->SetOtherTeleporter(pFirstBlueTeleporter);
                    pFirstBlueTeleporter = nullptr;
                }
                m_plevelData[index] = ' ';
                break;
            case '0':
                if (pFirstRedTeleporter == nullptr)
                {
                    pFirstRedTeleporter = new Teleporter(x, y, ActorColor::Red);
                    m_pActors.push_back(pFirstRedTeleporter);
                }
                else
                {
                    Teleporter* pSecondRedTeleporter = new Teleporter(x, y, ActorColor::Red);
                    m_pActors.push_back(pSecondRedTeleporter);
                    pFirstRedTeleporter->SetOtherTeleporter(pSecondRedTeleporter);
                    pSecondRedTeleporter->SetOtherTeleporter(pFirstRedTeleporter);
                    pFirstRedTeleporter = nullptr;
                }
                m_plevelData[index] = ' ';
                break;
            case 'o':
                if (pFirstGreenTeleporter == nullptr)
                {
                    pFirstGreenTeleporter = new Teleporter(x, y, ActorColor::Green);
                    m_pActors.push_back(pFirstGreenTeleporter);
                }
                else
                {
                    Teleporter* pSecondGreenTeleporter = new Teleporter(x, y, ActorColor::Green);
                    m_pActors.push_back(pSecondGreenTeleporter);
                    pFirstGreenTeleporter->SetOtherTeleporter(pSecondGreenTeleporter);
                    pSecondGreenTeleporter->SetOtherTeleporter(pFirstGreenTeleporter);
                    pFirstGreenTeleporter = nullptr;
                }
                m_plevelData[index] = ' ';
                break;
            case 'r':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, ActorColor::Red));
                break;
            case 'g':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, ActorColor::Green));
                break;
            case 'b':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Key(x, y, ActorColor::Blue));
                break;
            case 'R':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidRed));
                break;
            case 'G':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, ActorColor::Green, ActorColor::SolidGreen));
                break;
            case 'B':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Door(x, y, ActorColor::Blue, ActorColor::SolidBlue));
                break;
            case 'X':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Exit(x, y));
                break;
            case '$':
                m_plevelData[index] = ' ';
                m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
                break;
            case '@':
                m_plevelData[index] = ' ';
                if (PlayerX != nullptr)
                {
                    *PlayerX = x;
                    *PlayerY = y;
                }
                break;
            case 'e':
                m_pActors.push_back(new Enemy(x, y));
                m_plevelData[index] = ' '; // clear the level
                break;
            case'h':
                m_pActors.push_back(new Enemy(x, y, 3, 0));
                m_plevelData[index] = ' ';
                break;
            case 'v':
                m_pActors.push_back(new Enemy(x, y, 0, 2));
                m_plevelData[index] = ' '; // clear the level
                break;
            case 'L':
                m_pActors.push_back(new Lava(x, y, ActorColor::Yellow, ActorColor::SolidYellow));
                m_plevelData[index] = ' ';
                break;
            case ' ':
                    break;
                default:
                    cout << "Invaild character in level file: " << m_plevelData[index] << endl;
                    bool anyWarning = true;
                    break;


            }
        }
    }
    return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
    return x + y * m_width;
}

PlacableActor* Level::UpdateActors(int x, int y)
{
    PlacableActor* collidedActor = nullptr;

    for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
    {
        (*actor)->Update();

        if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition())
        {
            assert(collidedActor == nullptr);
            collidedActor = (*actor);
        }
    }
    return collidedActor;
}