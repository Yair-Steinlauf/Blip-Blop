#pragma once
#include "MovingState.h"




class LeftMovment : public MovingState
{
public:
	LeftMovment() = default;
	~LeftMovment() override = default;
	void enter(MovingEntity& entity) override;
	std::unique_ptr<MovingState> move() override;
};