#pragma once
#include "Strategy.h"
//================Forward declaration=======================
class MovingEntity;

class MoveStrategy : public Strategy{
public:
	MoveStrategy() = default;
	virtual sf::Vector2f move(MovingEntity& entity, float deltaTime) = 0;

};