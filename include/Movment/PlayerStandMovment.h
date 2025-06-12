#pragma once
#include "MovingState.h"

class StandMovement : public MovingState
{
public:
	StandMovement() = default;
	~StandMovement() override = default;
	void enter(MovingEntity& entity) override;
	std::unique_ptr<MovingState> move() override;

};