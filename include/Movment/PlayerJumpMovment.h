#pragma once
#include "MovingState.h"


class PlayerJumpMovement : public  MovingState {
public:
	MovingState::MovingState;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
private:
};