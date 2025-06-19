#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

class MovingState
{
public:

	MovingState(MoveComponent& moveComponent);
	virtual ~MovingState() = default;
	virtual void enter() = 0;
	virtual std::unique_ptr<MovingState> move() = 0;

protected:
	MoveComponent& m_moveComponent;
};