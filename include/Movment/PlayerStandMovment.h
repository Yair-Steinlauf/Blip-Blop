#pragma once
#include "MovingState.h"


class PlayerStandMovement : public MovingState
{
public:
	MovingState::MovingState;
	~PlayerStandMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;

};