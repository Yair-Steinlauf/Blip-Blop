#pragma once
#include "MovingEntity.h"

class MovingState
{
public:

	MovingState(MovingEntity& entity);
	virtual ~MovingState() = default;
	virtual void enter() = 0;
	virtual std::unique_ptr<MovingState> move() = 0;

protected:
	MovingEntity& m_entity;
};