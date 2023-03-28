#include <iostream>
#include "Lava.h"
#include <Windows.h>

Lava::Lava(int x, int y, ActorColor color, ActorColor closeColor)
	: PlacableActor(x, y, color)
	, m_closeColor(closeColor)
{

}

void Lava::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	SetConsoleTextAttribute(console, (int)m_closeColor);
	std::cout << 'L';
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}