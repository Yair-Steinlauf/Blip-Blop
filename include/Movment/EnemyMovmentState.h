#pragma once

#include "MovingState.h"

//TODO: Only for check, its a placeholder for the enemy movement state.
// yoou can do any algorythm you want here, dino/dragon etc.
class EnemyMovementState : public MovingState
{
public:
	EnemyMovementState() = default;
	~EnemyMovementState() override = default;

	void enter(MovingEntity& entity) override;
	std::unique_ptr<MovingState> move() override;
};