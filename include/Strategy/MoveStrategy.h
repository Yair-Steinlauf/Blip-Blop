#pragma once
#include "Strategy.h"
#include "MovingEntity.h"

class MoveStrategy : public Strategy{
public:
	MoveStrategy() = default;
	virtual sf::Vector2f move(MovingEntity& entity, float deltaTime) = 0;

};