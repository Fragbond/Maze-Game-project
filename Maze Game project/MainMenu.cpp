#include "MainMenu.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

MainMenu::MainMenu(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{

}

bool MainMenu::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::GamePlay);
		}
		else if ((char)input == kHighScore)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Highscore);
		}
		else if ((char)input == kSettings)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
	}
	return shouldQuit;
}

void MainMenu::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - MAIN MENU - - -" << endl << endl;
	cout << "             " << kPlay << ". Play" << endl;
	cout << "             " << kHighScore << ". Highscore" << endl;
	cout << "             " << kSettings << ". Settings" << endl;
	cout << "             " << kQuit << ". Quit" << endl;
}