#include <iostream>
#include "Exit.h"

Exit::Exit(int x, int y)
	:PlacableActor(x, y)
{

}

void Exit::Draw()
{
	std::cout << "X";
}