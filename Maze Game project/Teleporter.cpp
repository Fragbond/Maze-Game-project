#include "Teleporter.h"
#include "PlacableActor.h"
#include <iostream>
#include <Windows.h>
#include "GamePlayState.h"

void Teleporter::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "O";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Teleporter::TeleporterToLocation(int newPlayerX, int newPlayerY, Teleporter& target)
{
	//newPlayerX& newPlayerY == target.m_Teleporter;
}





