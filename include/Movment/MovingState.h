#pragma once
#include "MovingEntity.h"

class MovingState
{
public:
	MovingState() = default;
	virtual ~MovingState() = default;
	virtual void enter(MovingEntity& entity) = 0;
	virtual std::unique_ptr<MovingState> move() = 0;
};