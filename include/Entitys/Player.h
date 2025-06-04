#pragma once
#include "AttackingEntity.h"

class Player : public AttackingEntity
{
public:
	using AttackingEntity::AttackingEntity;
	Player();
	~Player() override = default;
	void handleInput(const sf::Event& event, float deltaTime);
private:
};
