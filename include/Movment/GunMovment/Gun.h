#pragma once
#include <memory>
#include "Movment/MoveComponent.h"

#include "GameAnimations.h"
class ShootingStrategy;
class Player;

class Gun
{
public:

	Gun(AnimationSet animationSet, std::unique_ptr<ShootingStrategy> strategy, float shootCooldown, const sf::Sound& shootSound);
	virtual ~Gun() = default;
	virtual void enter(Direction direction, Player* m_owner);
	virtual Direction move(sf::Vector2f mousePos, sf::Vector2f entityPos);
	std::vector<std::unique_ptr<BaseEntity>> shoot(sf::Vector2f mousePos, sf::Vector2f entityPos, b2World* world);
	void update(float deltaTime);
	void setStrategy(std::unique_ptr<ShootingStrategy> strategy);
	void setAnimationSet(AnimationSet set);
	void setshootCooldown(float shootCooldown);
	void setShootSound(const sf::Sound& sound);
private:
	std::unique_ptr<ShootingStrategy> m_strategy;

	Direction m_direction;
	AnimationSet m_weaponType;
	sf::Vector2f m_gunDirection;
	sf::Sound m_shootSound;

	float m_shootCooldown = 0.3f;
	float m_timeSinceLastShot = 0.0f;
};