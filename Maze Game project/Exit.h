#pragma once
#include "PlacableActor.h"

class Exit : public PlacableActor
{
public:
	Exit(int x, int y);
	
	virtual ActorType GetType() override { return ActorType::Exit; }
	virtual void Draw() override;
};
