#pragma once
#include "Movment/MovingState.h"

class PlayerRightMovement : public MovingState
{
public:
	using MovingState::MovingState;

	~PlayerRightMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};