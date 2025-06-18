#pragma once
#include "MovingState.h"


class PlayerLeftMovement : public MovingState
{
public:
	MovingState::MovingState;
	~PlayerLeftMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};