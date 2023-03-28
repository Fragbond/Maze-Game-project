#include "WinState.h"
#include "StateMachineExampleGame.h"
#include <iostream>
#include <conio.h>

using namespace std;

WinState::WinState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{

}

bool WinState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void WinState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - WELL DONE - - -" << endl << endl;
	cout << "              You beat the game!" << endl << endl;
	cout << "              Press any key to go back to the main menu" << endl << endl;
}