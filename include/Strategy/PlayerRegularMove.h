#pragma once
#include "MoveStrategy.h"

class PlayerRegularMove : public MoveStrategy
{
public:
	sf::Vector2f move(MovingEntity& entity, float deltaTime) override;
};