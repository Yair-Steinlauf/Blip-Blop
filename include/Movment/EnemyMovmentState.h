#pragma once
#include <memory>
#include "Movment/MovingState.h"
//TODO: Only for check, its a placeholder for the enemy movement state.
class EnemyMovementState : public MovingState
{
public:
	EnemyMovementState(MoveComponent& moveComponent) : MovingState(moveComponent) {}
	~EnemyMovementState() override = default;

	void enter() override;
	std::unique_ptr<MovingState> move() override;
};

//TODO: