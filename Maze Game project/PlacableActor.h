#pragma once
#include "Point.h"

enum class ActorColor
{
	Regular = 7,
	Yellow = 14,
	SolidYellow = 238,
	Green = 10,
	SolidGreen = 34,
	Red = 12,
    SolidRed = 68,
    Blue = 9,
	SolidBlue = 153,
};

enum class ActorType
{
	Door,
	Enemy,
	Exit,
	Key,
	Money,
	Player,
	Lava,
	Teleporter
};

class PlacableActor
{
public:
	PlacableActor(int x, int y, ActorColor color = ActorColor::Regular);
	virtual ~PlacableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);

	ActorColor GetColor() { return m_color; }

	void Remove() { m_IsActive = false; }
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	virtual ActorType GetType() = 0;
	virtual void Draw() = 0;
	virtual void Update()
	{

	}

protected:
	Point* m_pPosition;

	bool m_IsActive;
	ActorColor m_color;
};

