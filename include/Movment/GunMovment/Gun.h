#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

#include "GameAnimations.h"
class ShootingStrategy;
class Player;

class Gun
{
public:

	Gun(AnimationSet animationSet, std::unique_ptr<ShootingStrategy> strategy, float shootCooldown);
	virtual ~Gun() = default;
	virtual void enter(Direction direction, Player* m_owner);
	virtual Direction move(sf::Vector2f mousePos, sf::Vector2f entityPos);
	std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f mousePos, sf::Vector2f entityPos, b2World* world);
	void update(float deltaTime);
private:
	std::unique_ptr<ShootingStrategy> m_strategy;

	Direction m_direction;
	AnimationSet m_weaponType;
	sf::Vector2f m_gunDirection;

	float m_shootCooldown = 0.3f;
	float m_timeSinceLastShot = 0.0f;
};