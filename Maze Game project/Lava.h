#pragma once
#include "PlacableActor.h"

class Lava : public PlacableActor
{
public:
	Lava(int x, int y, ActorColor color, ActorColor closedColor);
	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Lava; }

private:
	ActorColor m_closeColor;
};