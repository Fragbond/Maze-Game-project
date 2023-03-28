#include "SettingState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "AudioManager.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingState::SettingState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool SettingState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kMainMenu)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);

		}
		else if ((char)input == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();
			AudioManager::GetInstance()->PlayMoneySound();
		}
	}
	return false;
}

void SettingState::Draw()
{
	system("cls");
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - Settings - - -" << endl << endl;
	cout << "             " << kSound << ". Toggle Sound ";
	if (AudioManager::GetInstance()->IsSoundOn())
	{
		cout << "ON" << endl;
	}
	else
	{
		cout << "OFF" << endl;
	}
	cout << "             " << kMainMenu << ". Back to Main Menu " << endl;
}