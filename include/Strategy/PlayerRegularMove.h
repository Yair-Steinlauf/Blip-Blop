#pragma once
#include "MoveStrategy.h"

class PlayerRegularMove : public MoveStrategy
{
public:
	using MoveStrategy::MoveStrategy; 
	
	sf::Vector2f setDirection(MovingEntity& entity, float deltaTime) override;
};