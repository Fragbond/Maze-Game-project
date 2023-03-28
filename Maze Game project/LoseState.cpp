#include "LoseState.h"
#include "StateMachineExampleGame.h"
#include <iostream>
#include <conio.h>

using namespace std;

LoseState::LoseState(StateMachineExampleGame* pOwner)
	:m_pOwner(pOwner)
{

}

bool LoseState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void LoseState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - Game Over - - -" << endl << endl;
	cout << "              Better luck next time!" << endl << endl;
	cout << "              Press any key to go back to the main menu" << endl << endl;
}