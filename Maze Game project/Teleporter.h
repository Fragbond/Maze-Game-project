#pragma once
#include "PlacableActor.h"
#include <string>

class Teleporter : public PlacableActor
{
	Teleporter* m_pOtherTeleporter;
public:
	Teleporter(int x, int y, ActorColor color)
		:PlacableActor(x, y, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Teleporter; }
	virtual void Draw() override;
	virtual void TeleporterToLocation(int newPlayerX, int newPlayerY, Teleporter& target);
	void SetOtherTeleporter(Teleporter* OtherTeleporter) { m_pOtherTeleporter = OtherTeleporter; }
	Teleporter* GetOtherTeleporter() { return m_pOtherTeleporter; }
};