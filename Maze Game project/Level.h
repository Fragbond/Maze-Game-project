#pragma once
#include <string>
#include <vector>

class PlacableActor;

class Level
{
	char* m_plevelData;
	int m_height;
	int m_width;

	std::vector<PlacableActor*> m_pActors;

public:
	Level();
	~Level();

	bool Load(std::string levelName, int* PlayerX, int* PlayerY);
	void Draw();
	PlacableActor* UpdateActors(int x, int y);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

	static constexpr char WAL = (char)219;

private:
	bool Convert(int* PlayerX, int* PlayerY);
	int GetIndexFromCoordinates(int x, int y);
};