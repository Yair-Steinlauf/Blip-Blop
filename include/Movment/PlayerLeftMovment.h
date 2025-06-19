#pragma once
#include "Movment/MovingState.h"


class PlayerLeftMovement : public MovingState
{
public:
	PlayerLeftMovement(MoveComponent& moveComponent) : MovingState(moveComponent) {}
	~PlayerLeftMovement() override = default;
	void enter() override;
	std::unique_ptr<MovingState> move() override;
};