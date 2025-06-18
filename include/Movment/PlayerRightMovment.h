#pragma once
#include "MovingState.h"

class PlayerRightMovement : public MovingState
{
public:
	MovingState::MovingState;
	~PlayerRightMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};