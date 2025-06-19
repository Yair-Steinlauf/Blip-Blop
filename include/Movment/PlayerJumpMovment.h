#pragma once
#include <memory>
#include "Movment/MovingState.h"


class PlayerJumpMovement : public MovingState {
public:
	using MovingState::MovingState;
	~PlayerJumpMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};