#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

#include "GameAnimations.h"

class GunState
{
public:

	GunState(MoveComponent& moveComponent);
	virtual ~GunState() = default;
	virtual void enter() = 0;
	virtual std::unique_ptr<GunState> move() = 0;

protected:
	MoveComponent& m_moveComponent;
};