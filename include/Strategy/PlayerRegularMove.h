#pragma once
#include "MoveStrategy.h"

class PlayerRegularMove : public MoveStrategy
{
public:
	using MoveStrategy::MoveStrategy; // Inherit constructor
	
	sf::Vector2f move(MovingEntity& entity, float deltaTime) override;
};