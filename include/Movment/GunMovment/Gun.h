#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

#include "GameAnimations.h"

class Gun
{
public:

	Gun(MoveComponent& moveComponent);
	virtual ~Gun() = default;
	virtual void enter(Direction direction);
	virtual Direction move(sf::Vector2f mousePos, sf::Vector2f entityPos);
protected:
	MoveComponent& m_moveComponent;
	Direction m_direction;
};