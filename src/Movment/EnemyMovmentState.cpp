#include "EnemyMovmentState.h"
#include "EnemyMovmentState.h"

void EnemyMovementState::enter(MovingEntity& entity)
{
	entity.setDirection({ 1.f, 0.f }); 
}

std::unique_ptr<MovingState> EnemyMovementState::move()
{
	return nullptr;
}