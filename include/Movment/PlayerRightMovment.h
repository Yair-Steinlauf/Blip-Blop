#pragma once
#include "MovingState.h"
class RightMovment : public MovingState
{
public:
	RightMovment() = default;
	~RightMovment() override = default;
	void enter(MovingEntity& entity) override;
	std::unique_ptr<MovingState> move() override;
};