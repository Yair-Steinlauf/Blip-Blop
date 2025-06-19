#pragma once
#include <memory>
#include "Movment/MovingState.h"


class PlayerStandMovement : public MovingState
{
public:
	using MovingState::MovingState;

	~PlayerStandMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};