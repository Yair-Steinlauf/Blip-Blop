#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

#include "GameAnimations.h"
class Player;

class Gun
{
public:

	Gun(AnimationSet animationSet, Player* owner);
	virtual ~Gun() = default;
	virtual void enter(Direction direction);
	virtual Direction move(sf::Vector2f mousePos, sf::Vector2f entityPos);
	void shoot(sf::Vector2f mousePos, sf::Vector2f entityPos);
protected:
	//MoveComponent& m_moveComponent;
	Direction m_direction;
	AnimationSet m_weaponType;
	Player* m_owner;
};