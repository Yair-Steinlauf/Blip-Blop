#pragma once
#include <memory>
#include "Movment/MovingState.h"
#include <functional>

//TODO: Only for check, its a placeholder for the enemy movement state.
class EnemyMovementState : public MovingState
{
public:
	EnemyMovementState(MoveComponent& moveComponent, std::function<sfPos()> playerloc) : MovingState(moveComponent), m_getPlayerLoc(playerloc) {}
	~EnemyMovementState() override = default;

	void enter() override {};
	std::unique_ptr<MovingState> move() override;
private:
	std::function<sfPos()> m_getPlayerLoc;
	sf::Vector2f calculateDirectionToPlayer(const sfPos& enemyPos, const sfPos& playerPos) const;
};

//TODO: