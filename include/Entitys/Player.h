#pragma once
#include "BaseEntity.h"
#include "Movment/MoveComponent.h"
#include "Subject.h"
#include "Movment/MovingState.h"
#include "Movment/GunMovment/Gun.h"

class GamePlay;
class Player : public BaseEntity, public Subject
{
public:
	Player(sfPos pos = { 0,0 }, b2World* world = nullptr);
	~Player() override = default;
	void update(float deltaTime) override;
	void setGamePlay(GamePlay* gamePlay);
	void drawLifeBar(sf::RenderWindow& window);
	void addLife(int life);
	void setGun(std::unique_ptr<ShootingStrategy> strategy, AnimationSet weaponType, float shootCooldown);
private:
	void updateLifeBarSprite();
	MoveComponent m_moveComponent;
	GamePlay* m_gamePlay = nullptr;
	std::unique_ptr<Gun> m_gun;
	sf::Sprite m_lifeBar;
};
